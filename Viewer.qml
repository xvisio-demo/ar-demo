import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: viewer
    color: "black"

    Loader{
        id: loader
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: tabbar.top

        function page( index ){
            switch( index ){
            case 0: return Qt.resolvedUrl("ImageDisplay.qml");
            case 1: return Qt.resolvedUrl("VR.qml");
            case 2: return Qt.resolvedUrl("AR.qml");
            }
        }

        source: page( tabbar.currentIndex )
    }

    TabBar{
        id: tabbar
        width: parent.width
        anchors.bottom: parent.bottom
        currentIndex: 0

        TabButton {
            text: qsTr("Camera")
        }
        TabButton {
            text: qsTr("VR")
        }
        TabButton {
            text: qsTr("AR")
        }

        onCurrentIndexChanged: {
            control.reset()
        }
    }
}
