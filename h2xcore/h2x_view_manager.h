#ifndef H2XCORE_H2X_VIEW_MANAGER__H
#define H2XCORE_H2X_VIEW_MANAGER__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

    /*
    * ClassName: ViewManager
    * Desc: 视图类管理器类，负责整个页视图的调度管理，一个应用只允许有一个视图管理器，由Application对象直接管理
    * Author: zfs
    * Date: 2021-05-27 21:57
    */
    class H2XCORE_EXPORT ViewManager {
    public:
        ViewManager();
        virtual ~ViewManager();
    };

} // end namespace h2x

#endif // !H2XCORE_H2X_VIEW_MANAGER__H
