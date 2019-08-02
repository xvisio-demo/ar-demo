import Qt3D.Core 2.12
import Qt3D.Render 2.12
import Qt3D.Extras 2.12

import PathMesh 1.0

Entity {
    id: root

    property alias path: mesh.path
    property alias mesh: mesh
    property alias color: mat.ambient
    property alias effect: mat.effect
    property alias transform: transform


    property Material material: PhongMaterial {
        id: mat
        ambient: "yellow"
    }

    PathMesh {
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
