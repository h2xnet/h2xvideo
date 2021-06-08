#ifndef H2XBASE_TASK_MESSAGE_PUMP__H
#define H2XBASE_TASK_MESSAGE_PUMP__H

#include "build/build_config.h"
#include "h2xbase/h2x_base_export.h"

namespace h2x {

class TimeTicks;

/*
* ClassName: MessagePump
* Desc: 消息泵类
* Author: zfs
* Date: 2021-06-08 21:27
*/
class H2XBASE_EXPORT MessagePump {
public:
    // Delegate是一个回调类，让MessagePump给机会利用它处理其他任务。
    //   DoWork用来处理即时任务，这类任务需要尽可能快地被开始处理
    //   DoDelayedWork用来处理定时任务，这类任务在特定时刻被处理，next_delayed_message_time为下个任务执行的时刻
    //   DoIdleWork用来处理闲时任务，这类任务在MessagePump处于空闲状态时被处理
    // 三者返回值意义类似，返回true表示处理了该类任务，返回false表示没有该类任务需要处理
    class H2XBASE_EXPORT Delegate {
    public:
        virtual ~Delegate() {}

        virtual bool doWork() = 0;
        virtual bool doDelayedWork(TimeTicks *next_delayed_message_time) = 0;
        virtual bool doIdleWork() = 0;
    };

    MessagePump();
    virtual ~MessagePump();

    // 启动消息循环
    virtual void run(Delegate* delegate) = 0;

    // 通知退出消息循环
    virtual void quit() = 0;

    // 通知MessagePump处理即时任务
    // 可以跨线程调用这个接口
    virtual void scheduleWork() = 0;

    // 通知MessagePump处理定时任务
    // 此接口不允许跨线程调用
    virtual void scheduleDelayedWork(const TimeTicks& delay_message_time) = 0;

};

} // end namespace h2x

#endif // !H2XBASE_TASK_MESSAGE_PUMP__H
