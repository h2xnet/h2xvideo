#ifndef H2XCORE_H2X_OBJECT__H
#define H2XCORE_H2X_OBJECT__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

    /*
    * ClassName: Object
    * Desc: 对象类，用于扩展一些数据类型
    * Author: zfs
    * Date: 2021-05-27 22:45
    */
    class H2XCORE_EXPORT Object {
    public:
        Object();
        virtual ~Object();
    };

} // end namespace h2x

#endif // !H2XCORE_H2X_OBJECT__H
