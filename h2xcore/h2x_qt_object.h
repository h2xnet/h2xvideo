#ifndef H2XCORE_H2X_QT_OBJECT__H
#define H2XCORE_H2X_QT_OBJECT__H

#include "h2xcore/h2x_core_export.h"
#include "h2xcore/h2x_object.h"

namespace h2x {

    /*
    * ClassName: QTObject
    * Desc: QT对象类，对Object类的扩展，用于支持QT对象
    * Author: zfs
    * Date: 2021-05-27 22:45
    */
class H2XCORE_EXPORT QTObject : public Object {
public:
    QTObject();
    virtual ~QTObject();
};

} // end namespace h2x

#endif // !H2XCORE_H2X_QT_OBJECT__H
