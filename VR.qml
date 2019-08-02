import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Scene3D 2.0
import Qt3D.Render 2.0

Item {

    property int screenshot: 0

    focus: true

    Component.onCompleted: {
        forceActiveFocus()
    }

    Keys.onSpacePressed: {
        scene3d.grabToImage(function(result) {
                                   result.saveToFile("img_vr_" + screenshot + ".png");
                                   screenshot++
                               });
    }

    Keys.onPressed: {
        if( event.text == "r" ){
            control.reset()
            root.reset();
        }
        if( event.text == "s" ){
            control.generateSurface()
        }
    }

    Scene3D {
        id: scene3d
        anchors.fill: parent
        focus: true
        aspects: ["input", "logic"]
        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

        SceneRootVR {
            id: root
        }
    }

    CheckBox{
        id: cameraView
        text: qsTr("Camera View")
    }
}
