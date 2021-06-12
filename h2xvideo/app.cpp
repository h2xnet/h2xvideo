#include "h2xvideo/app.h"

#include "h2xvideo/main_view.h"

App::App() : Application(0, NULL, NULL) {

}

App::App(int argc, char *argv[], const h2x::Config* cfg) : Application(argc, argv, cfg) {

}

App::~App() {

}

void App::registViews() {
    qmlRegisterType<MainView>("component.h2xvideo.mainviewhandler", 1, 0, "MainViewHandler");
}

void App::beforeStart() {
    // ע��ҳ�������
    this->registViews();
}

void App::onStarted() {

}