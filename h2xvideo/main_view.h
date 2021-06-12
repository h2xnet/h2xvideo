#ifndef H2XVIDEO_MAIN_VIEW__H
#define H2XVIDEO_MAIN_VIEW__H

#include "h2xcore/h2x_view.h"
#include <QObject>
#include <QtQml>

class MainView : public QObject, public h2x::View {
    Q_OBJECT
public:
    // �Ե����ķ�ʽ�ṩ��QMLʹ��
    static MainView* qmlAttachedProperties(QObject *object);

    explicit MainView(QObject* parent = nullptr);
    virtual ~MainView();
};

#endif // !H2XVIDEO_MAIN_VIEW__H
