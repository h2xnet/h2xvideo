import QtQuick 2.3

import component.h2xvideo.mainview 1.0

Rectangle {
    width: 200
    height: 100
    color: "red"

    Text {
        anchors.centerIn: parent
        text: "Hello, World!, login!"
    }

     MouseArea {
        anchors.fill: parent
        onClicked: {
            MainView.routerPageSet("login", "");
        }
    }
}
