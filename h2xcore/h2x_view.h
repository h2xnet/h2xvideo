#ifndef H2XCORE_H2X_VIEW__H
#define H2XCORE_H2X_VIEW__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

/*
* ClassName: View
* Desc: 视图类，负责与QML页面交互，提供后台业务与QML页面的中介，
* 通常建议一个QML页面对应一个View视图类，每一个视图类都是一个单例，由视图管理器根据路由配置统一调度管理
* Author: zfs
* Date: 2021-05-16 17:40
*/
class H2XCORE_EXPORT View {
public:
    View();
    virtual ~View();
};

} // end namespace h2x

#endif // !H2XCORE_H2X_VIEW__H
