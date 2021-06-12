#include "h2xvideo/app.h"

#include "h2xvideo/MainView.h"

App::App() : Application(0, NULL, NULL) {

}

App::App(int argc, char *argv[], const h2x::Config* cfg) : Application(argc, argv, cfg) {

}

App::~App() {

}

void App::registViews() {
    qmlRegisterType<MainView>("component.h2xvideo.mainview", 1, 0, "MainView");
}

void App::beforeStart() {
    // ×¢²áÒ³Ãæ¿ØÖÆÀà
    this->registViews();
}

void App::onStarted() {

}