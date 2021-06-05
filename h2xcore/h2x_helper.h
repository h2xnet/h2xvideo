#ifndef H2XCORE_H2X_HELPER__H
#define H2XCORE_H2X_HELPER__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Context;

/*
    * ClassName: Helper
    * Desc: 帮助函数类，用于封装一些公共算法，每次创建上下文对象时会同时创建一个帮助函数类对象
    * Author: zfs
    * Date: 2021-06-05 11:42
    */
class H2XCORE_EXPORT Helper {
public:
    Helper();
    virtual ~Helper();

private:
    // 请求上下文对象
    Context* ctx_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_HELPER__H
