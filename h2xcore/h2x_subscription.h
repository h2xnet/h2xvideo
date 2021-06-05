#ifndef H2XCORE_H2X_SUBSCRIPTION__H
#define H2XCORE_H2X_SUBSCRIPTION__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

/*
* ClassName: Subscription
* Desc: 消息订阅类，用于各个应用模块组件向框架订阅消息
* Author: zfs
* Date: 2021-06-05 12:25
*/
class H2XCORE_EXPORT Subscription {
public:
    Subscription();
    virtual ~Subscription();

};

} // end namespace h2x

#endif // !H2XCORE_H2X_SUBSCRIPTION__H
