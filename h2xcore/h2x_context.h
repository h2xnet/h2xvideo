#ifndef H2XCORE_H2X_CONTEXT__H
#define H2XCORE_H2X_CONTEXT__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

/*
* ClassName: Context
* Desc: 请求数据结构类，每次请求，框架都会实例化一个Context对象
* Author: zfs
* Date: 2021-05-16 17:20
*/
class H2XCORE_EXPORT Context {
public:
    Context();
    virtual ~Context();
};

} // end namespace h2x

#endif // !H2XCORE_H2X_CONTEXT__H
