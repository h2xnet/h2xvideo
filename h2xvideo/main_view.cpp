#include "h2xvideo/main_view.h"

MainView* MainView::qmlAttachedProperties(QObject *object) {
    static MainView* inst = NULL;
    if (!inst) {
        inst = new MainView(object);
    }
    return inst;
}

MainView::MainView(QObject* parent) : QObject(parent) {

}

MainView::~MainView() {

}