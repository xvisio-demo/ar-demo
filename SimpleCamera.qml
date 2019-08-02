import Qt3D.Core 2.0
import Qt3D.Render 2.0
import QtQuick 2.0 as QQ2

Entity {
    property CameraLens lens: null

    components: [
        lens,
        camera
    ]

   /* CameraLens{
        id: lens
        projectionType: CameraLens.FrustumProjection
        projectionMatrix: Qt.matrix4x4(1,0,0,0,
                                       0,1,0,0,
                                       0,0,1,0,
                                       0,0,0,1)
    }*/

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: fov.value
        aspectRatio: window.width / window.height
        nearPlane: 0.0001
        farPlane: 1000.0
        position: Qt.vector3d(0.0, 10.0, 20.0)
        viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
        upVector: Qt.vector3d(0.0, 1.0, 0.0)


        QQ2.Connections{
            target: control
            onCameraPoseChanged:{
                camera.position = tools.move( control.cameraPose, control.cameraOrientation, Qt.vector3d(0,0,0) )
                camera.viewCenter = tools.move( camera.position, control.cameraOrientation, Qt.vector3d(0,0,-1) )
                camera.upVector = tools.move( Qt.vector3d(0,0,0), control.cameraOrientation, Qt.vector3d(0,-1,0) )
                //camera.position = tools.move( control.cameraPose, control.cameraOrientation, Qt.vector3d(0,0,0.5) )
                //camera.viewCenter = tools.move( camera.position, control.cameraOrientation, Qt.vector3d(0,0,-2) ) //Qt.vector3d(cameraPose.x,cameraPose.y,cameraPose.z-2)
                //camera.upVector = Qt.vector3d(0.0, 1.0, 0.0)
            }
            onCameraOrientationChanged:{
                camera.position = tools.move( control.cameraPose, control.cameraOrientation, Qt.vector3d(0,0,0) )
                camera.viewCenter = tools.move( camera.position, control.cameraOrientation, Qt.vector3d(0,0,-1) )
                camera.upVector = tools.move( Qt.vector3d(0,0,0), control.cameraOrientation, Qt.vector3d(0,-1,0) )
                //camera.position = tools.move( control.cameraPose, control.cameraOrientation, Qt.vector3d(0,0,0.5) )
                //camera.viewCenter = tools.move( camera.position, control.cameraOrientation, Qt.vector3d(0,0,-2) ) //Qt.vector3d(cameraPose.x,cameraPose.y,cameraPose.z-2)
                //camera.upVector = Qt.vector3d(0.0, 1.0, 0.0)
            }
        }
    }
}
