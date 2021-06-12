#ifndef H2XVIDEO_APP__H
#define H2XVIDEO_APP__H

#include "h2xcore/h2x_application.h"

namespace h2x {

class Config;
class View;

}

/*
 * ClassName : App
 * Desc: 应用类，一个应用只允许包含一个应用对象
 * Author: zhaofushou
 * Date: 2021-06-12 15:36
 */
class App : public h2x::Application {
public:
    App();
    App(int argc, char *argv[], const h2x::Config* cfg);

    virtual ~App();

    /*
     * FunctionName: registViews
     * Desc: 注册QML视图控制器,注册的视图类中的函数可以被QML调用
     */
    void registViews();

    /*
     * FunctionName: beforeStart
     * Desc: 当应用服务启动前，会调用此函数回调通知，一个应用只会通知一次
     * Author: zfs
     * Date: 2021-06-12 15:40
     */
    virtual void beforeStart() override;

    /*
     * FunctionName: onStarted
     * Desc: 当应用服务启动完成后，会调用此函数回调通知，一个应用只会通知一次
     * Author: zfs
     * Date: 2021-06-12 15:41
     */
    virtual void onStarted() override;
};

extern App& getApp();

#endif // !H2XVIDEO_APP__H
