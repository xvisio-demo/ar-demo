import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.12

import CameraMesh 1.0

Entity {
    id: root

    property alias width: mesh.width
    property alias height: mesh.height
    property alias depth: mesh.depth
    property alias transform: transform

    property alias effect: mat.effect
    property color color: "white"
    property double thickness: 1.0

    property Material material:  PhongMaterial {
        id: mat
        ambient: root.color
        parameters: [
            Parameter { name: "color"; value: root.color },
            Parameter { name: "line.color"; value: 5.0 }
        ]
    }

    CameraMesh {
        id: mesh
    }

    Transform {
        id: transform
        translation: Qt.vector3d(0, 0, 0)
    }

    components: [
        mesh,
        transform,
        material
    ]
}
