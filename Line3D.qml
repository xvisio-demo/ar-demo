import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.12

import LineMesh 1.0

Entity {
    id: root
    property alias from: mesh.from
    property alias to: mesh.to
    property alias effect: mat.effect
    property color color: "white"
    property double thickness: 1.0
    property alias transform: transform

    property Material material:  PhongMaterial {
        id: mat
        ambient: root.color
        parameters: [
            Parameter { name: "color"; value: root.color },
            Parameter { name: "line.color"; value: 5.0 }
        ]
    }

    LineMesh {
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
