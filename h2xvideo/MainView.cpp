#include "h2xvideo/MainView.h"

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

void MainView::routerPageSet(QString pageName, QString pageParam) {
    // ֪ͨҳ��ı�
    emit routerPageChanged(pageName, pageParam);
}