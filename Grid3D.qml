import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.12

import GridMesh 1.0

Entity {
    id: root

    property alias width: mesh.width
    property alias height: mesh.height
    property alias size: mesh.resolution
    property alias transform: transform

    property color color: "black"
    property alias effect: mat.effect


    property Material material:  PhongMaterial {
        id: mat
        ambient: root.color
        parameters: [
            Parameter { name: "color"; value: root.color },
            Parameter { name: "line.color"; value: 5.0 }
        ]
    }

    /*property Material material: Material {
        id: mat

        property color ambient: Qt.rgba( 0.9, 0.05, 0.05, 1.0 )
        //property color diffuse: Qt.rgba( 0.9, 0.7, 0.7, 1.0 )
        //property color specular: Qt.rgba( 0.95, 0.55, 0.55, 1.0 )
        //property color ambient: Qt.rgba( 0.05, 0.05, 0.05, 1.0 )
        //property color diffuse: Qt.rgba( 0.7, 0.7, 0.7, 1.0 )
        //property color specular: Qt.rgba( 0.95, 0.95, 0.95, 1.0 )
        property real shininess: 150.0
        property real lineWidth: 0.8
        property color lineColor: Qt.rgba( 0.0, 0.0, 0.0, 1.0 )

        parameters: [
            Parameter { name: "ka"; value: Qt.vector3d(mat.ambient.r, mat.ambient.g, mat.ambient.b) },
            //Parameter { name: "kd"; value: Qt.vector3d(root.diffuse.r, root.diffuse.g, root.diffuse.b) },
            //Parameter { name: "ksp"; value: Qt.vector3d(root.specular.r, root.specular.g, root.specular.b) },
            Parameter { name: "shininess"; value: mat.shininess },
            Parameter { name: "line.width"; value: mat.lineWidth },
            Parameter { name: "line.color"; value: mat.lineColor },
            Parameter { name: "color"; value: "green" }
        ]
    }*/



    GridMesh {
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
