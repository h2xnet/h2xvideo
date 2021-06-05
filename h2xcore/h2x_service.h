#ifndef H2XCORE_H2X_SERVICE__H
#define H2XCORE_H2X_SERVICE__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Application;
class Context;
class Logger;

/*
* ClassName: Service
* Desc: 服务类，用于处理业务
* Author: zfs
* Date: 2021-05-16 17:38
*/
class H2XCORE_EXPORT Service {
public:
    Service();
    virtual ~Service();

private:
    // 应用对象
    Application* app_;

    // 请求上下文
    Context* ctx_;

    // 当前服务日志
    Logger* log_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_SERVICE__H
