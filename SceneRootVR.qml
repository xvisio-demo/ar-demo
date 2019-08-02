import Qt3D.Core 2.0
import Qt3D.Render 2.12
import Qt3D.Extras 2.12
import Qt3D.Animation 2.12
import Qt3D.Input 2.0
import QtQuick 2.0 as QQ2


Entity {
    id: sceneRoot

    function reset(){
        path.mesh.clear()
    }

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: window.width / window.height
        nearPlane: 0.01
        farPlane: 1000.0
        position: Qt.vector3d(0.0, 1.0, -5.0)
        viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
        upVector: Qt.vector3d(0.0, 1.0, 0.0)

        function updatePose(){
            if( cameraView.checked ){
                camera.viewCenter = tools.move( control.cameraPose, control.cameraOrientation, Qt.vector3d(0,0,1) )
                camera.position = control.cameraPose
                camera.upVector = tools.move( Qt.vector3d(0,0,0), control.cameraOrientation, Qt.vector3d(0,1,0) )
            }
        }

        QQ2.Connections{
            target: control
            onCameraPoseChanged:{
                camera.updatePose()
            }
            onCameraOrientationChanged:{
                camera.updatePose()
            }
        }
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                id: renderer
                camera: camera
                clearColor: Qt.rgba(0.0, 0.4, 0.7, 1.0)
                viewportRect: Qt.rect(0,0,1,1)

                RenderStateSet {
                    renderStates: [
                        LineWidth { value: 5 }
                    ]
                }
            }
        },
        InputSettings { }
    ]


    Entity {
        components: [
            PointLight {
                color: "white"
                intensity: 0.3
                constantAttenuation: 1.0
                linearAttenuation: 0.0
                quadraticAttenuation: 0.0025
            },
            Transform {
                translation: Qt.vector3d(0.0, 10.0, 0.0)
            }
        ]
    }


    OrbitCameraController {
        camera: camera
    }

    Grid3D{
        width: 20
        height: 20
        size: Qt.size(20,20)
        color: "white"
        transform.translation: Qt.vector3d(-10, -0.75, -10)
    }

    Path3D{
        id: path

        QQ2.Connections{
            target: control
            onCameraPoseChanged:{
                path.mesh.push( control.cameraPose )
            }
        }
    }

    Camera3D{
        id: cameraDisplay
        color: "red"

        width: 0.5
        height: 0.3
        depth: 0.3

        enabled: !cameraView.checked

        QQ2.Connections{
            target: control
            onCameraPoseChanged:{
                cameraDisplay.transform.translation.x = cameraPose.x
                cameraDisplay.transform.translation.y = cameraPose.y
                cameraDisplay.transform.translation.z = cameraPose.z
            }
            onCameraOrientationChanged:{
                cameraDisplay.transform.rotation = cameraOrientation
            }
        }
    }

    ToyPlane{
        enabled: true
        transform.translation: Qt.vector3d(-0.75, 0, 2)
    }

    Sphere3D{
        color: "red"
        radius: 1
        transform.translation: Qt.vector3d(-4, 0, -4)
    }

    Voxel3D{
        transform.translation: Qt.vector3d(2, -0.125, -2)
    }
}
