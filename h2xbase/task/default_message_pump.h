#ifndef H2XBASE_TASK_DEFAULT_MESSAGE_PUMP__H
#define H2XBASE_TASK_DEFAULT_MESSAGE_PUMP__H

#include "h2xbase/task/message_pump.h"
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/time/time.h"
#include "h2xbase/sync/waitable_event.h"

namespace h2x {

class H2XBASE_EXPORT DefaultMessagePump : public MessagePump {
public:
    DefaultMessagePump();
    virtual ~DefaultMessagePump() {}

    virtual void run(Delegate* delegate);
    virtual void quit();
    virtual void scheduleWork();
    virtual void scheduleDelayedWork(const TimeTicks& delay_message_time);

private:
    void onWait();
    void onWaitTimeout(const TimeDelta &timeout);
    void onWakeup();

    WaitableEvent event_;
    bool should_quit_;
    TimeTicks delayed_work_time_;

    DISALLOW_COPY_AND_ASSIGN(DefaultMessagePump);
};

} // end namespace h2x

#endif // !H2XBASE_TASK_DEFAULT_MESSAGE_PUMP__H
