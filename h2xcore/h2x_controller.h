#ifndef H2XCORE_H2X_CONTROLLER__H
#define H2XCORE_H2X_CONTROLLER__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Application;
class Context;
class Logger;

/*
* ClassName: Controller
* Desc: 控制器类
* Author: zfs
* Date: 2021-05-16 17:20
*/
class H2XCORE_EXPORT Controller {
public:
    Controller(Application* app, Context* ctx);
    virtual ~Controller();

private:
    // 应用对象
    Application* app_;

    // 上下文对象
    Context* ctx_;

    // 为当前控制器封装的日志对象
    Logger* log_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_CONTROLLER__H
