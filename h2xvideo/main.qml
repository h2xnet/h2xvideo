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
    // RouterStackView : 路由
    // 
    RouterStackView {
        id: routerStackView
    }

    //
    // HomeView : 首页页面
    //
    HomeView {
        id: homeView
        name: "home"
    }

    //
    // LoginView : 登录页面
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
    // onRouterPageChanged : 路由页面改变
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
