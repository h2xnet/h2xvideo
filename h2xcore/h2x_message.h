#ifndef H2XCORE_H2X_MESSAGE__H
#define H2XCORE_H2X_MESSAGE__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

    /*
    * ClassName: Message
    * Desc: 消息处理类，当任务执行完成后，负责进行通知
    * Author: zfs
    * Date: 2021-05-27 21:51
    */
    class H2XCORE_EXPORT Message {
    public:
        Message();
        virtual ~Message();
    };

} // end namespace h2x

#endif // !H2XCORE_H2X_MESSAGE__H
