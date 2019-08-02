import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.12

import CloudMesh 1.0

Entity {
    id: root

    property alias cloud: mesh.cloud
    property alias mesh: mesh
    property alias color: mat.ambient
    property alias effect: mat.effect
    property alias transform: transform


    property Material material:  PhongMaterial {
        id: mat
        ambient: "yellow"
        parameters: [
            Parameter { name: "color"; value: root.color },
            Parameter { name: "line.color"; value: 5.0 }
        ]
    }

    CloudMesh {
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
