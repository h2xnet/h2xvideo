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

    /*// test
    CrashWinHandle* h = new CrashWinHandle();
    h2x::CrashWin cw(h);
    cw.Regist(h2x::CrashWin::ExceptionLevel::error);

    Sleep(2000);

    //char* ptr = NULL;
    //delete ptr;
    strcpy(NULL, "adfadfg"); // »√≥Ã–Ú±¿¿£
    // end test*/

    return app.exec();
}
