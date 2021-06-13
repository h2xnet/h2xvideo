#include "h2xvideo/main_view_handler.h"

#include "h2xvideo/app.h"

MainViewHandler* MainViewHandler::qmlAttachedProperties(QObject *object) {
    static MainViewHandler* inst = NULL;
    if (!inst) {
        inst = new MainViewHandler(object);
    }
    return inst;
}

MainViewHandler::MainViewHandler(QObject* parent) : QObject(parent) {

}

MainViewHandler::~MainViewHandler() {

}

void MainViewHandler::routerPageSet(QString sender, QString pageName, QString pageParam) {

    getApp().getLogger().PrintLogW(h2x::Logger::ContentType::Info, L"MainViewHandler::routerPageSet sender:%s pageName:%s, pageParam:%s\n",
        reinterpret_cast<const wchar_t*>(sender.utf16()),
        reinterpret_cast<const wchar_t*>(pageName.utf16()),
        reinterpret_cast<const wchar_t*>(pageParam.utf16()));

    // 通知页面改变
    emit routerPageChanged(sender, pageName, pageParam);
}