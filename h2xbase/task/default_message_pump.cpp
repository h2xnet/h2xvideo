#include "h2xbase/task/default_message_pump.h"

#include <assert.h>

namespace h2x {


    DefaultMessagePump::DefaultMessagePump() :
        event_(false, false),
        should_quit_(0) {

    }

    void DefaultMessagePump::run(Delegate* delegate)
    {
        // Quit must have been called outside of Run!
        assert(should_quit_ == false);

        for (;;)
        {
            bool did_work = delegate->doWork();
            if (should_quit_)
                break;

            did_work |= delegate->doDelayedWork(&delayed_work_time_);
            if (should_quit_)
                break;

            if (did_work)
                continue;

            did_work = delegate->doIdleWork();
            if (should_quit_)
                break;

            if (did_work)
                continue;

            if (delayed_work_time_.is_null())
            {
                onWait();
            }
            else
            {
                TimeDelta delay = delayed_work_time_ - TimeTicks::Now();
                if (delay > TimeDelta())
                    onWaitTimeout(delay);
                else
                {
                    // It looks like delayed_work_time_ indicates a time in the past, so we
                    // need to call DoDelayedWork now.
                    delayed_work_time_ = TimeTicks();
                }
            }
        }

        should_quit_ = false;
    }

    void DefaultMessagePump::quit()
    {
        should_quit_ = true;
    }

    void DefaultMessagePump::scheduleWork()
    {
        // Since this can be called on any thread, we need to ensure that our Run
        // loop wakes up.
        onWakeup();
    }

    void DefaultMessagePump::scheduleDelayedWork(const TimeTicks& delayed_work_time)
    {
        // We know that we can't be blocked on Wait right now since this method can
        // only be called on the same thread as Run, so we only need to update our
        // record of how long to sleep when we do sleep.
        delayed_work_time_ = delayed_work_time;
    }

    void DefaultMessagePump::onWait()
    {
        event_.Wait();
    }

    void DefaultMessagePump::onWaitTimeout(const TimeDelta &timeout)
    {
        event_.WaitTimeout(timeout);
    }

    void DefaultMessagePump::onWakeup()
    {
        event_.Signal();
    }

} // end namespace h2x