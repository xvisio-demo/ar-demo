import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import QtQuick.Scene3D 2.12

import ImagePainter 1.0
import QtQuick.Extras 1.4

Rectangle {
    id: window
    color: "black"

    Component.onCompleted: {
        mainContent.forceActiveFocus()
    }

    ShaderEffectSource {
        id: shaderEffectSource
        sourceItem: scene3d
    }

    Rectangle{
        focus: true
        id: mainContent
        color: "white"
        anchors.fill: parent

        property int screenshot: 0

        Keys.onSpacePressed: {
            mainContent.grabToImage(function(result) {
                                       result.saveToFile("img_ar_" + screenshot + ".png");
                                       screenshot++
                                   });
        }

        Keys.onPressed: {
            if( event.text == "h" ){
                controls.visible = !controls.visible
            }
            if( event.text == "r" ){
                control.reset()
            }
        }

        ImagePainter{
            id: left
            anchors.fill: parent
            mirrored: true

            Connections{
                target: control
                onNewLeftImage: {
                    left.image = image
                }
            }
        }

        Scene3D {
            visible: !distortion.checked
            id: scene3d
            anchors.fill: parent
            focus: true
            aspects: ["input", "logic", "animation"]
            cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

            SceneRootAR {
                id: root
            }
        }

        ShaderEffect {
            visible: distortion.checked
            anchors.fill: parent
            property variant source: shaderEffectSource
            property real f1: f1Slider.value
            property real f2: f2Slider.value
            property real xi1: xi1Slider.value
            property real xi2: xi2Slider.value
            //vertexShader: "qrc:/shaders/fisheye.vert"
            fragmentShader: "qrc:/shaders/fisheye.frag"
        }

        Column{
            id: controls
            width: parent.width
            anchors.bottom: parent.bottom
            visible: false

            CheckBox{
                id: distortion
                text: "Use distortion"
                checked: true
            }
            SliderPicker{
                id: fov
                from: 1.0
                to: 179
                value: 120
            }
            SliderPicker {
                id: f1Slider
                from: 1.0
                to: 1000.0
                value: 115.0
            }
            SliderPicker {
                id: f2Slider
                from: 1.0
                to: 1000
                value: 575.0
            }
            SliderPicker {
                id: xi1Slider
                from: 0.0
                to: 1.0
                value: 0.0
            }
            SliderPicker {
                id: xi2Slider
                from: 0.0
                to: 1.0
                value: 1.0
            }
        }

        StatusIndicator{
            active: true
            color: "red"
            visible: control.lost
        }
    }

    Label{
        id: hints
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 5
        text: qsTr("Press 'R' to reset")

        Timer{
            running: hints.visible
            interval: 2500
            onTriggered: {
                hints.visible = false
            }
        }
    }
}
