import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainViewHandler 1.0

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
    //RouterStackView {
    //    id: routerStackView
    //}
    StackView {
        id: routerStackView
        anchors.fill: parent
    }

    //
    // HomeView : ��ҳҳ��
    //
    HomeView {
        id: homeView
        visible: false
        pageName: "home"
        pageParam: ""
    }

    //
    // LoginView : ��¼ҳ��
    //
    LoginView {
        id: loginView
        visible: false
        pageName: "login"
        pageParam: ""
    }

    Component.onCompleted: {
        console.log("main.qml Component.onCompleted.")
        // ������ҳ
        mainViewHandler.routerPageSet("main", "home", "");
    }

    /*MouseArea {
        anchors.fill: parent
        onClicked: {
            mainWin.close()
        }
    }*/

    //
    // onRouterPageChanged : ·��ҳ��ı�
    //

    MainViewHandler {
        id: mainViewHandler

        // �ź�
        onRouterPageChanged : function(sender, pageName, pageParam) {
            console.log("main.qml MainViewHandler.onRouterPageChanged.");
            let paramObj = {
                sender: sender,
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
    

}
