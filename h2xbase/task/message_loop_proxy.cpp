#include "h2xbase/task/message_loop_proxy.h"

namespace h2x {

MessageLoopProxy::~MessageLoopProxy() {

}

bool MessageLoopProxy::postTask(const StdClosure &task) {
    return postTaskHelper(task, TimeDelta(), true);
}

bool MessageLoopProxy::postDelayedTask(
    const StdClosure& task, TimeDelta delay) {
    return postTaskHelper(task, delay, true);
}

bool MessageLoopProxy::postNonNestableTask(const StdClosure &task) {
    return postTaskHelper(task, TimeDelta(), false);
}

bool MessageLoopProxy::postNonNestableDelayedTask(
    const StdClosure& task, TimeDelta delay) {
    return postTaskHelper(task, delay, false);
}

bool MessageLoopProxy::belongsToCurrentThread() {
    std::unique_lock<std::mutex> lock(message_loop_lock_);
    return (target_message_loop_ &&
        (MessageLoop::current() == target_message_loop_));
}


// MessageLoop::DestructionObserver implementation
void MessageLoopProxy::willDestroyCurrentMessageLoop() {
    std::unique_lock<std::mutex> lock(message_loop_lock_);
    target_message_loop_ = nullptr;
}

void MessageLoopProxy::onDestruct()
{
    bool delete_later = false; {
        std::unique_lock<std::mutex> lock(message_loop_lock_);
        if (target_message_loop_ &&
            (MessageLoop::current() != target_message_loop_))
        {
            target_message_loop_->postNonNestableTask(
                std::bind(&MessageLoopProxy::DeleteSelf, this));
            delete_later = true;
        }
    }
    if (!delete_later)
        delete this;
}

void MessageLoopProxy::DeleteSelf() const {
    delete this;
}

MessageLoopProxy::MessageLoopProxy()
    : target_message_loop_(MessageLoop::current()) {

}

bool MessageLoopProxy::postTaskHelper(
    const StdClosure& task, TimeDelta delay, bool nestable) {
    std::unique_lock<std::mutex> lock(message_loop_lock_);
    if (target_message_loop_) {
        if (nestable) {
            if (delay == TimeDelta())
                target_message_loop_->postTask(task);
            else
                target_message_loop_->postDelayedTask(task, delay);
        }
        else {
            if (delay == TimeDelta())
                target_message_loop_->postNonNestableTask(task);
            else
                target_message_loop_->postNonNestableDelayedTask(task, delay);
        }
        return true;
    }
    return false;
}

std::shared_ptr<MessageLoopProxy> MessageLoopProxy::current() {
    MessageLoop* cur_loop = MessageLoop::current();
    if (!cur_loop)
        return nullptr;
    return cur_loop->message_loop_proxy();
}

void MessageLoopProxyTraits::destruct(const MessageLoopProxy* proxy) {
    if (proxy) {
        ((MessageLoopProxy*)proxy)->onDestruct();
    }
}


} // end namespace h2x