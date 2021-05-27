#ifndef H2XCORE_H2X_DISPATCH__H
#define H2XCORE_H2X_DISPATCH__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

    /*
    * ClassName: Dispatch
    * Desc: 任务分发器类，负责基于路由对控制器进行调度
    * Author: zfs
    * Date: 2021-05-16 17:20
    */
    class H2XCORE_EXPORT Dispatch {
    public:
        Dispatch();
        virtual ~Dispatch();
    };

} // end namespace h2x

#endif // !H2XCORE_H2X_DISPATCH__H
