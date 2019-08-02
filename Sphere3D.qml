import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.12

Entity{

    property alias color: mat.ambient
    property alias radius: mesh.radius
    property alias transform: transform

    id: cameraCenter
    property Material material:  PhongMaterial {
        id: mat
        ambient: "green"
        parameters: [
            Parameter { name: "color"; value: mat.ambient },
            Parameter { name: "line.color"; value: 5.0 }
        ]
    }

    SphereMesh {
        id: mesh
        radius: 0.01
        //rings: 8
        //slices: 4
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
