#ifndef H2XVIDEO_MAIN_VIEW__H
#define H2XVIDEO_MAIN_VIEW__H

#include "h2xcore/h2x_view.h"
#include <QObject>
#include <qstring.h>
#include <QtQml>

class MainView : public QObject, public h2x::View {
    Q_OBJECT
public:
    // 以单例的方式提供给QML使用
    static MainView* qmlAttachedProperties(QObject *object);

    explicit MainView(QObject* parent = nullptr);
    virtual ~MainView();

public:
    /*
     * FunctionName: routerPageSet
     * Desc: 设置路由页面
     */
    Q_INVOKABLE void routerPageSet(QString pageName, QString pageParam = QString(""));

public Q_SLOTS:
    // 

Q_SIGNALS:
    // 信号列表
    /*
     * FunctionName: routerPageChanged
     * Desc: 路由页面发生改变
     * Author: zfs
     * Date: 2021-06-12 22:35
     * @pageName: 页面名称
     * @pageParam: 页面参数，可以为空，
     */
    void routerPageChanged(QString pageName, QString pageParam = QString(""));

private:
};

#endif // !H2XVIDEO_MAIN_VIEW__H
