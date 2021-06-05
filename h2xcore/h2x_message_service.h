#ifndef H2XCORE_H2X_MESSAGE_SERVICE__H
#define H2XCORE_H2X_MESSAGE_SERVICE__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

/*
* ClassName: MessageService
* Desc: 消息服务类，提供消息订阅服务
* Author: zfs
* Date: 2021-06-05 12:20
*/
class H2XCORE_EXPORT MessageService {
public:
    MessageService();
    virtual ~MessageService();
};

} // end namespace h2x

#endif // !H2XCORE_H2X_MESSAGE_SERVICE__H
