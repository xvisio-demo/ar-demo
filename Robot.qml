import Qt3D.Core 2.12
import Qt3D.Render 2.12
import Qt3D.Extras 2.12
import Qt3D.Animation 2.12
import Qt3D.Input 2.0
import QtQuick 2.0 as QQ2

Entity {
    id: entity
    property double scale: 0.0025

    SkinnedPbrEffect {
        id: texturedSkinnedPbrEffect
        useTextures: true
    }

    AnimationClipLoader {
        id: animationClip
        source: "qrc:/robot/robot-dance.gltf"

        function play(){
            riggedFigure1.running = false
            riggedFigure1.start()
        }

        QQ2.Component.onCompleted: {
            play()
        }
    }

    AnimatedEntity {
        id: riggedFigure1
        enabled: control.arReady && !control.lost
        transform.scale: entity.scale
        transform.rotationX: 90
        transform.rotationZ: 180

        transform.translation: control.arCenter

        source: "qrc:/robot/robot-dance.gltf"
        clip: animationClip
        playbackRate: 1.0

        effect: texturedSkinnedPbrEffect
        textureBaseName: "qrc:/robot/robot"
        textureBaseColor: "_red"
    }
}
