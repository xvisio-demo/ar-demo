import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    Column{
        anchors.centerIn: parent
        spacing: 20
        BusyIndicator{
            anchors.horizontalCenter: parent.horizontalCenter
            running: true
        }
        Label{
            text: qsTr("Please connect the camera")
        }
    }
}
