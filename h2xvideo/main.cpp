#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "h2xbase/crash/crash_win.h"

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

    // ���÷�EXE����Ŀ¼�µ�DLLĿ¼��������ʱ����
    //SetDllDirectory()


    return app.exec();
}
