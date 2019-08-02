import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.12

import PointMesh 1.0

Entity {
    id: root

    property double xSize: 10.0
    property double ySize: 10.0
    property double zSize: 10.0
    property color color: Qt.rgba(1.0,0,0,0.5)
    property alias effect: mat.effect
    property alias transform: transform

    property Material material:  PhongMaterial {
        id: mat
        ambient: root.color
        parameters: [
            Parameter { name: "color"; value: root.color },
            Parameter { name: "maincolor"; value: root.color }
        ]
    }

    CuboidMesh {
        id: mesh
        xExtent: root.xSize
        yExtent: root.ySize
        zExtent: root.zSize
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
