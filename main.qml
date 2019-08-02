import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 448
    title: qsTr("XSlam AR Demo")

    property bool ready: false

    Loader{
        anchors.fill: parent
        source: ready ? Qt.resolvedUrl("Viewer.qml") : Qt.resolvedUrl("SplashScreen.qml")
    }

    Timer{
        running: !ready
        interval: 500
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            if( control.cameraAvailable() ){
                ready = true
                control.start()
            }
        }
    }
}
