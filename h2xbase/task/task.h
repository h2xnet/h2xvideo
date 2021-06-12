#ifndef H2XBASE_TASK_TASK__H
#define H2XBASE_TASK_TASK__H

#include "h2xbase/task/callback.h"
#include "h2xbase/time/time.h"
#include "h2xbase/h2x_base_export.h"
#include <assert.h>

namespace h2x {

/*struct H2XBASE_EXPORT PendingTask {
    PendingTask(const StdClosure& task) : std_task(task), sequence_num(0){}

    PendingTask(const StdClosure &task,
        h2x::TimeTicks delayed_run_time) : std_task(task), delayed_run_time(delayed_run_time),
        sequence_num(0) {}

    ~PendingTask() {}

    // 用于优先队列的排序，std::heap默认为大顶堆，
    // 而我们要的是小顶堆，所以这个操作符重载实际得返回大于的比较结果
    bool operator<(const PendingTask& other) const {
        if (delayed_run_time > other.delayed_run_time)
            return true;
        if (delayed_run_time < other.delayed_run_time)
            return false;
        return sequence_num > other.sequence_num;
    }

    // 任务被运行的时刻，这个也用于鉴别定时任务与非定时任务
    h2x::TimeTicks delayed_run_time;
    // 定时任务序号，可作为定时任务的第二排序键，非定时任务此项无效
    int sequence_num;

    void Run() {
        if (std_task) {
            std_task();
        }
        else {
            assert(false);
        }
    }

private:
    StdClosure std_task;
};*/

} // end namespace h2x

#endif // !H2XBASE_TASK_TASK__H
