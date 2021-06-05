#ifndef H2XCORE_H2X_MIDDLEWARE__H
#define H2XCORE_H2X_MIDDLEWARE__H

#include "h2xbase/task/task.h"
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Context;

/*
* ClassName: Middleware
* Desc: 中间件类
* 注意：框架和插件加载的中间件会在应用层配置的中间件之前，框架默认中间件不能被应用层中间件覆盖，
* 如果应用层有自定义同名中间件，在启动时会报错。
* Author: zfs
* Date: 2021-05-16 17:29
*/
class H2XCORE_EXPORT Middleware {
public:
    Middleware(Context* ctx);
    virtual ~Middleware();

private:
    // 上下文对象
    Context* ctx_;

    // next函数
};

} // end namespace h2x

#endif // !H2XCORE_H2X_MIDDLEWARE__H
