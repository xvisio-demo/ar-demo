import Qt3D.Core 2.0
import Qt3D.Render 2.10
import Qt3D.Extras 2.12

Entity{
    property Transform transform: Transform {
        id: toyplaneTransform
        translation: Qt.vector3d(0,0,5)
        scale: 0.1
    }

    PhongMaterial{
        id: toyplaneMaterial
        ambient: "darkgreen"
        parameters: [
            Parameter { name: "color"; value: toyplaneMaterial.ambient },
            Parameter { name: "maincolor"; value: toyplaneMaterial.ambient }
        ]
    }

    Mesh {
        id: toyplaneMesh
        source: "qrc:/objects/toyplane.obj"
    }


    components: [
        toyplaneMesh,
        toyplaneTransform,
        toyplaneMaterial
    ]
}
