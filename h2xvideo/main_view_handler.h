#ifndef H2XVIDEO_MAIN_VIEW_HANDLER__H
#define H2XVIDEO_MAIN_VIEW_HANDLER__H

#include "h2xcore/h2x_view.h"
#include <QObject>
#include <qstring.h>
#include <QtQml>

class MainViewHandler : public QObject/*, public h2x::View*/ {
    Q_OBJECT
public:
    // 以单例的方式提供给QML使用
    static MainViewHandler* qmlAttachedProperties(QObject *object);

    explicit MainViewHandler(QObject* parent = nullptr);
    virtual ~MainViewHandler();

    /*
     * FunctionName: routerPageSet
     * Desc: 设置路由页面
     */
    Q_INVOKABLE void routerPageSet(QString sender, QString pageName, QString pageParam = QString(""));


public:

    // 信号
signals:
    // 信号列表
    /*
     * FunctionName: routerPageChanged
     * Desc: 路由页面发生改变
     * Author: zfs
     * Date: 2021-06-12 22:35
     * @sender: 发送者
     * @pageName: 页面名称
     * @pageParam: 页面参数，可以为空，
     */
    void routerPageChanged(QString sender, QString pageName, QString pageParam = QString(""));

    // 
public slots:

private:
};

#endif // !H2XVIDEO_MAIN_VIEW_HANDLER__H
