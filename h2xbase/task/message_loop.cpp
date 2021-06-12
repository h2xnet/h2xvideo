#include "h2xbase/task/message_loop.h"

#include "h2xbase/task/default_message_pump.h"
#include "h2xbase/task/message_loop_proxy.h"

#include <assert.h>
#include "h2xbase/memory/lazy_instance.h"
#include "h2xbase/thread/thread_local.h"

namespace h2x {

LazyInstance<ThreadLocalPointer<MessageLoop> > g_lazy_ptr;

MessageLoop::MessageLoop() : type_(kDefaultMessageLoop), state_(NULL), nestable_tasks_allowed_(true),
next_delayed_task_sequence_num_(0) {
    // 一个线程内不能存在两个或以上MessageLoop
    assert(g_lazy_ptr.pointer()->get() == NULL);
    // 默认消息循环
    if (type_ == kDefaultMessageLoop) {
        pump_.reset(new DefaultMessagePump);
    }
    g_lazy_ptr.pointer()->set(this);

    message_loop_proxy_.reset(new MessageLoopProxy, &MessageLoopProxyTraits::destruct);
    message_loop_proxy_->target_message_loop_ = this;
}

MessageLoop::~MessageLoop() {
    bool has_work = false;

    // 清理未处理的任务可能导致生成新的任务，
    // 这里通过有限次的循环尝试清理这些新生成的任务
    for (int i = 0; i < 100; i++)
    {
        deletePendingTasks();
        reloadWorkQueue();
        has_work = deletePendingTasks();
        if (!has_work)
            break;
    }

    assert(!has_work);

    preDestruct();

    message_loop_proxy_->willDestroyCurrentMessageLoop();
    message_loop_proxy_ = nullptr;

    g_lazy_ptr.pointer()->set(NULL);
}

MessageLoop* MessageLoop::current()
{
    return g_lazy_ptr.pointer()->get();
}

void MessageLoop::run() {
    assert(this == current());
    AutoRunState state(this);
    runInternal();
}

void MessageLoop::runAllPending() {
    assert(this == current());
    AutoRunState state(this);
    state_->quit_received = true;  // Means run until we would otherwise block.
    runInternal();
}

void MessageLoop::runInternal() {
    assert(this == current());

    pump_->run(this);
}

bool MessageLoop::deletePendingTasks() {
    bool has_work = false;
    while (!work_queue_.empty())
    {
        PendingTask task = work_queue_.front();
        work_queue_.pop();
        if (!task.delayed_run_time.is_null())
            addToDelayedWorkQueue(task);
    }

    while (!deferred_non_nestable_work_queue_.empty())
        deferred_non_nestable_work_queue_.pop();

    has_work = !delayed_work_queue_.empty();
    while (!delayed_work_queue_.empty())
        delayed_work_queue_.pop();

    return has_work;
}

void MessageLoop::quit() {
    if (state_) {
        state_->quit_received = true;
    }
}

void MessageLoop::quitNow() {
    if (pump_) {
        pump_->quit();
    }
}

void MessageLoop::postTask(const StdClosure &task) {
    PendingTask pending_task(task);
    addToIncomingQueue(pending_task);
}

void MessageLoop::postDelayedTask(const StdClosure &task, TimeDelta delay) {
    PendingTask pending_task(task,
        TimeTicks::Now() + delay,
        true);
    addToIncomingQueue(pending_task);
}

void MessageLoop::postNonNestableTask(const StdClosure &task) {
    PendingTask pending_task(task,
        TimeTicks(),
        false);
    addToIncomingQueue(pending_task);
}

void MessageLoop::postNonNestableDelayedTask(const StdClosure &task, TimeDelta delay) {
    PendingTask pending_task(task,
        TimeTicks::Now() + delay,
        false);
    addToIncomingQueue(pending_task);
}

TimeTicks MessageLoop::evalDelayedRuntime(int64_t delay_ms) {
    TimeTicks delayed_run_time;
    if (delay_ms > 0)
        delayed_run_time = TimeTicks::Now() + TimeDelta::FromMilliseconds(delay_ms);
    return delayed_run_time;
}

void MessageLoop::addToIncomingQueue(const PendingTask &task) {
    // 本方法可能会在另一个线程中被执行，所以必须线程安全
    std::shared_ptr<MessagePump> pump;
    {
        std::unique_lock<std::mutex> lock(incoming_queue_lock_);
        bool was_empty = incoming_queue_.empty();
        incoming_queue_.push(task);
        if (!was_empty) {
            return;
        }
        // 因为这函数可能是间接地在另一个线程中被调用的，
        // 此时MessageLoop中可能正有任务在运行，
        // 这些任务中可能包含销毁MessageLoop的任务，
        // 为了保证对MessageLoop中的MessagePump引用有效，
        // 这里需要用到引用指针
        pump = pump_;
    }
    pump->scheduleWork();
}

void MessageLoop::addToDelayedWorkQueue(const PendingTask &task) {
    PendingTask new_task(task);
    new_task.sequence_num = next_delayed_task_sequence_num_++;
    delayed_work_queue_.push(new_task);
}

void MessageLoop::reloadWorkQueue() {
    if (!work_queue_.empty()) {
        return;
    }

    {
        std::unique_lock<std::mutex> lock(incoming_queue_lock_);
        if (incoming_queue_.empty())
            return;
        // 常数时间交换内存
        work_queue_.swap(&incoming_queue_);
    }
}

bool MessageLoop::deferOrRunPendingTask(const PendingTask &task)
{
    // 任务符合立即执行的条件，那么执行之
    if (task.nestable || state_->run_depth == 1)
    {
        runTask(task);
        return true;
    }
    // 不可嵌套任务，需要缓存之直到在最顶层MessageLoop中执行
    deferred_non_nestable_work_queue_.push(task);
    return false;
}

void MessageLoop::runTask(const PendingTask &task)
{
    assert(nestable_tasks_allowed_);

    // 考虑到最坏情况下，任务可能是不可重入的，
    // 所以暂时禁用嵌套任务

    nestable_tasks_allowed_ = false;
    PendingTask pending_task = task;
    preProcessTask();
    pending_task.run();
    postPrecessTask();
    nestable_tasks_allowed_ = true;
}

bool MessageLoop::doWork() {
    // 任务当前是否允许被执行
    if (!nestable_tasks_allowed_)
        return false;

    for (;;)
    {
        // 先从incoming队列取任务
        reloadWorkQueue();
        if (work_queue_.empty())
            break;

        // 一次性处理work队列中的所有任务
        do
        {
            PendingTask task = work_queue_.front();
            work_queue_.pop();
            if (!task.delayed_run_time.is_null())
            {
                // 加入到定时任务队列
                addToDelayedWorkQueue(task);
                // 如果加入的新任务是将被最先执行的，那么需要重新调度
                if (delayed_work_queue_.top().sequence_num == task.sequence_num)
                    pump_->scheduleDelayedWork(task.delayed_run_time);
            }
            else
            {
                if (deferOrRunPendingTask(task))
                    return true;
            }
        } while (!work_queue_.empty());
    }

    return false;
}

bool MessageLoop::doDelayedWork(TimeTicks *next_delayed_message_time) {
    if (!next_delayed_message_time) {
        return false;
    }
    if (!nestable_tasks_allowed_ || delayed_work_queue_.empty())
    {
        *next_delayed_message_time = recent_tick_ = TimeTicks();
        return false;
    }

    // recent_tick_记录最近一次调用TimeTick::Now时的时间，
    // 它不能代替TimeTick::Now，它是只是一个过去的Now的缓存，
    // 用来最大限度减少对TimeTick::Now的调用。
    // recent_tick_用来进行第一轮判断，要进行精确判断需要更新它为真正的TimeTick::Now

    TimeTicks next_run_time = delayed_work_queue_.top().delayed_run_time;
    if (next_run_time > recent_tick_)
    {
        // 可能是recent_tick_的不精确性引起，需要更新之
        recent_tick_ = TimeTicks::Now();
        if (next_run_time > recent_tick_)
        {
            // 真的是一个将来才需要被运行的任务，留到将来运行
            *next_delayed_message_time = next_run_time;
            return false;
        }
    }

    // 这个定时任务运行时刻已到，运行之
    PendingTask task = delayed_work_queue_.top();
    delayed_work_queue_.pop();

    if (!delayed_work_queue_.empty())
        *next_delayed_message_time = delayed_work_queue_.top().delayed_run_time;

    return deferOrRunPendingTask(task);
}


bool MessageLoop::processNextDelayedNonNestableTask() {
    // 嵌套任务？
    if (state_->run_depth != 1)
        return false;

    if (deferred_non_nestable_work_queue_.empty())
        return false;

    PendingTask task = deferred_non_nestable_work_queue_.front();
    deferred_non_nestable_work_queue_.pop();
    runTask(task);
    return true;
}

bool MessageLoop::doIdleWork() {
    // 进入Idle状态后，先尝试执行被缓存着的非嵌套任务
    if (processNextDelayedNonNestableTask())
        return true;

    // 检查退出标记
    if (state_->quit_received)
        pump_->quit();

    return false;
}

void MessageLoop::setNestableTasksAllowed(bool allowed) {
    if (nestable_tasks_allowed_ != allowed)
    {
        nestable_tasks_allowed_ = allowed;
        if (!nestable_tasks_allowed_)
            return;
        pump_->scheduleWork();
    }
}

void MessageLoop::addDestructionObserver(DestructionObserver *observer) {
    assert(this == current());
    destruction_observers_.AddObserver(observer);
}

void MessageLoop::removeDestructionObserver(DestructionObserver *observer) {
    assert(this == current());
    destruction_observers_.RemoveObserver(observer);
}

void MessageLoop::addTaskObserver(TaskObserver *observer) {
    assert(this == current());
    task_observers_.AddObserver(observer);
}

void MessageLoop::removeTaskObserver(TaskObserver *observer) {
    assert(this == current());
    task_observers_.RemoveObserver(observer);
}

void MessageLoop::preDestruct() {
    size_t index = 0;
    DestructionObserver* observer;
    AutoLazyEraser lazy_eraser(&destruction_observers_);
    while (index < destruction_observers_.GetObserverCount())
    {
        observer = destruction_observers_.GetObserver(index++);
        if (observer == NULL)
            continue;
        observer->PreDestroyCurrentMessageLoop();
    }
}

void MessageLoop::preProcessTask() {
    size_t index = 0;
    TaskObserver* observer;
    AutoLazyEraser lazy_eraser(&task_observers_);
    while (index < task_observers_.GetObserverCount())
    {
        observer = task_observers_.GetObserver(index++);
        if (observer == NULL)
            continue;
        observer->preProcessTask();
    }
    // NOT compact the observer list, here
}

void MessageLoop::postPrecessTask() {
    size_t index = 0;
    TaskObserver* observer;
    AutoLazyEraser lazy_eraser(&task_observers_);
    while (index < task_observers_.GetObserverCount())
    {
        observer = task_observers_.GetObserver(index++);
        if (observer == NULL)
            continue;
        observer->postProcessTask();
    }
}


// the AutoRunState class
MessageLoop::AutoRunState::AutoRunState(MessageLoop* loop) : loop_(loop) {
    // Make the loop reference us.
    previous_state_ = loop_->state_;
    if (previous_state_) {
        run_depth = previous_state_->run_depth + 1;
    }
    else {
        run_depth = 1;
    }
    loop_->state_ = this;

    // Initialize the other fields:
    quit_received = false;
}

MessageLoop::AutoRunState::~AutoRunState() {
    loop_->state_ = previous_state_;
}

MessageLoop::PendingTask::PendingTask(const StdClosure &task)
    : std_task(task), nestable(true), sequence_num(0) {

}

MessageLoop::PendingTask::PendingTask(const StdClosure &task, TimeTicks delayed_run_time, bool nestable) :
    std_task(task), delayed_run_time(delayed_run_time),
    nestable(nestable), sequence_num(0) {

}

MessageLoop::PendingTask::~PendingTask() {

}

bool MessageLoop::PendingTask::operator<(const MessageLoop::PendingTask& other) const {
    if (delayed_run_time > other.delayed_run_time)
        return true;
    if (delayed_run_time < other.delayed_run_time)
        return false;
    return sequence_num > other.sequence_num;
}

} // end namespace h2x