#ifndef H2XCORE_H2X_OPTION__H
#define H2XCORE_H2X_OPTION__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

/*
* ClassName: Option
* Desc: 选项基类， 用于传递配置参数
* Author: zfs
* Date: 2021-06-05 22:00
*/
class H2XCORE_EXPORT Option {
public:
    Option();
    virtual ~Option();

};

} // end namespace h2x

#endif // !H2XCORE_H2X_OPTION__H
