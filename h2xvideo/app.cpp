#include "h2xvideo/app.h"

#include "h2xvideo/main_view_handler.h"

#include <qqml.h>

App::App() : Application(0, NULL, NULL) {

}

App::App(int argc, char *argv[], const h2x::Config* cfg) : Application(argc, argv, cfg) {

}

void App::operator=(const App& other) {
    this->argc_ = other.argc_;
    this->argv_ = other.argv_;
    this->cfg_ = other.cfg_;
}

App::~App() {

}

void App::registViews() {
    qmlRegisterType<MainViewHandler>("module.h2xvideo.mainViewHandler", 1, 0, "MainViewHandler");
}

void App::beforeStart() {
    // ×¢²áÒ³Ãæ¿ØÖÆÀà
    this->registViews();
}

void App::onStarted() {

}