import QtQuick 2.9
import QtQuick.Window 2.2

import component.h2xvideo.mainview 1.0

import "qrc:/qmluilib/router"

Window {
    id: mainWin
    visible: true
    flags: Qt.Dialog | Qt.FramelessWindowHint
    x: 0
    y: 0
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    //
    // RouterStackView : ·��
    // 
    RouterStackView {
        id: routerStackView
    }

    //
    // HomeView : ��ҳҳ��
    //
    HomeView {
        id: homeView
        name: "home"
    }

    //
    // LoginView : ��¼ҳ��
    //
    LoginView {
        id: loginView
        name: "login"
    }

    Component.onCompleted: {
        routerStackView.push(loginView)
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            mainWin.close()
        }
    }

    //
    // onRouterPageChanged : ·��ҳ��ı�
    //
    MainView.onRouterPageChanged : function(pageName, pageParam) {
        let paramObj = {
            pageName: pageName,
            pageParam: pageParam
        }
        console.log("main.qml MainViewHandler.onRouterPageChanged params: " + JSON.stringify(paramObj));

        if (pageName === "home") {
            routerStackView.push(loginView)
        }
        else if (pageName === "login") {
            routerStackView.push(homeView)
        }

    }
}
