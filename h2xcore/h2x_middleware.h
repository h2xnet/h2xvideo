#ifndef H2XCORE_H2X_MIDDLEWARE__H
#define H2XCORE_H2X_MIDDLEWARE__H

#include "h2xbase/task/task.h"
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Context;

/*
* ClassName: Middleware
* Desc: 中间件类
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
