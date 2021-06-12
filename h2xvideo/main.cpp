#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "h2xvideo/app.h"
#include "h2xvideo/app_config.h"
#include "h2xbase/crash/crash_win.h"

namespace {
    static AppConfig g_app_cfg_;
    static App g_app_;
}

App& getApp() {
    return g_app_;
}

class CrashWinHandle : public h2x::CrashHandler {
public:
};

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    // 设置非EXE所在目录下的DLL目录，进行延时加载
    //SetDllDirectory()

    // 初始化应用
    g_app_ = App(argc, argv, &g_app_cfg_);

    // 执行应用
    if (!g_app_.exec()) {

    }

    return app.exec();
}
