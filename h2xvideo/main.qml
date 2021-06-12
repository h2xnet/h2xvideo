import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: mainWin
    visible: true
    flags: Qt.Dialog | Qt.FramelessWindowHint
    x: 0
    y: 0
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    title: qsTr("Hello World")

    MouseArea {
        anchors.fill: parent
        onClicked: {
            mainWin.close()
        }
    }
}
