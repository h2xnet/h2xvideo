#ifndef H2XCORE_H2X_QT_VIEW__H
#define H2XCORE_H2X_QT_VIEW__H

#include "h2xcore/h2x_core_export.h"
#include "h2xcore/h2x_view.h"

namespace h2x {

    /*
    * ClassName: QTView
    * Desc: QT��ͼ��,View��ͼ����չ�������˶�QT��QML֧��
    * Author: zfs
    * Date: 2021-05-16 17:40
    */
    class H2XCORE_EXPORT QTView : public View {
    public:
        QTView();
        virtual ~QTView();
    };

} // end namespace h2x

#endif // !H2XCORE_H2X_QT_VIEW__H
