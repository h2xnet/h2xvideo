#ifndef H2XBASE_TASK_MESSAGE_LOOP_PROXY__H
#define H2XBASE_TASK_MESSAGE_LOOP_PROXY__H

#include "build/build_config.h"
#include <mutex>
#include <memory>
#include "h2xbase/task/message_loop.h"
#include "h2xbase/task/callback.h"
#include "h2xbase/time/time.h"
#include "h2xbase/h2x_base_export.h"

#include <assert.h>

namespace h2x {

class MessageLoop;

class MessageLoopProxy;
struct H2XBASE_EXPORT MessageLoopProxyTraits {
    static void destruct(const MessageLoopProxy* proxy);
};

/*
* ClassName: MessageLoopProxy
* Desc: 消息循环处理代理类，主要用于处理跨线程的消息
*/
class H2XBASE_EXPORT MessageLoopProxy : public SupportWeakCallback {
public:

    static std::shared_ptr<MessageLoopProxy> current();

    virtual ~MessageLoopProxy();

    // MessageLoopProxy implementation
    virtual bool postTask(const StdClosure &task);
    virtual bool postDelayedTask(const StdClosure &task,
        TimeDelta delay);
    virtual bool postNonNestableTask(const StdClosure &task);
    virtual bool postNonNestableDelayedTask(const StdClosure &task,
        TimeDelta delay);

    template<typename T1, typename T2>
    bool postTaskAndReply(const std::function<T1>& task, const std::function<T2>& reply)
    {
        PostTaskAndReplyRelay<T1, T2>* relay = new PostTaskAndReplyRelay<T1, T2>(task, reply);
        if (!postTask(std::bind(&PostTaskAndReplyRelay<T1, T2>::Run, relay))) {
            delete relay;
            return false;
        }

        return true;
    }

    virtual bool belongsToCurrentThread() const;

private:
    // Allow the messageLoop to create a MessageLoopProxy.
    friend class MessageLoop;
    friend struct MessageLoopProxyTraits;

    MessageLoopProxy();

    // Called directly by MessageLoop::~MessageLoop.
    virtual void willDestroyCurrentMessageLoop();
    // Called when the reference decreased to 0
    virtual void onDestruct();

    bool postTaskHelper(const StdClosure& task,
        TimeDelta delay,
        bool nestable);

    void DeleteSelf() const;

    // The lock that protects access to target_message_loop_.
    //mutable NLock message_loop_lock_;
    std::mutex message_loop_lock_;
    MessageLoop* target_message_loop_;

private:
    // This relay class remembers the MessageLoop that it was created on, and
    // ensures that both the |task| and |reply| Closures are deleted on this same
    // thread. Also, |task| is guaranteed to be deleted before |reply| is run or
    // deleted.
    //
    // If this is not possible because the originating MessageLoop is no longer
    // available, the the |task| and |reply| Closures are leaked.  Leaking is
    // considered preferable to having a thread-safetey violations caused by
    // invoking the Closure destructor on the wrong thread.
    class MessageLoopProxyNull
    {

    };

    template<typename T1, typename T2>
    class PostTaskAndReplyRelay : public SupportWeakCallback
    {
    public:
        PostTaskAndReplyRelay(const std::function<T1>& task, const std::function<T2>& reply)
            : origin_loop_(MessageLoopProxy::current())
        {
            std_task_ = task;
            std_reply_ = reply;
        }

        void run()
        {
            auto ret = std_task_();
            origin_loop_->PostTask(
                std::bind(&PostTaskAndReplyRelay::RunReplyAndSelfDestructWithParam<decltype(ret)>, this, ret));
        }

        ~PostTaskAndReplyRelay()
        {
            assert(origin_loop_->belongsToCurrentThread());
            std_task_ = nullptr;
            std_reply_ = nullptr;
        }

    private:
        void runReplyAndSelfDestruct() {
            assert(origin_loop_->belongsToCurrentThread());

            // Force |task_| to be released before |reply_| is to ensure that no one
            // accidentally depends on |task_| keeping one of its arguments alive while
            // |reply_| is executing.
            std_task_ = nullptr;

            std_reply_();

            // Cue mission impossible theme.
            delete this;
        }

        template<typename InernalT>
        void runReplyAndSelfDestructWithParam(InernalT ret) {
            assert(origin_loop_->BelongsToCurrentThread());

            // Force |task_| to be released before |reply_| is to ensure that no one
            // accidentally depends on |task_| keeping one of its arguments alive while
            // |reply_| is executing.
            std_task_ = nullptr;

            std_reply_(ret);

            // Cue mission impossible theme.
            delete this;
        }

        std::shared_ptr<MessageLoopProxy> origin_loop_;

        std::function<T2> std_reply_;
        std::function<T1> std_task_;
    };

};


template<>
void MessageLoopProxy::PostTaskAndReplyRelay<void(), void()>::run()
{
    std_task_();
    origin_loop_->postTask(
        std::bind(&PostTaskAndReplyRelay::runReplyAndSelfDestruct, this));
}

} // end namespace h2x

#endif // !H2XBASE_TASK_MESSAGE_LOOP_PROXY__H
