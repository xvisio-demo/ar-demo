import Qt3D.Core 2.12
import Qt3D.Render 2.12
import Qt3D.Extras 2.12
import Qt3D.Animation 2.12
import Qt3D.Input 2.12
import QtQuick 2.12 as QQ2


Entity {
    id: sceneRoot


    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 120
        aspectRatio: window.width / window.height
        nearPlane: 0.0001
        farPlane: 1000.0
        position: Qt.vector3d(0.0, 10.0, 20.0)
        viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
        upVector: Qt.vector3d(0.0, 1.0, 0.0)

        function updatePose(){
            camera.viewCenter = tools.move( control.cameraPose, control.cameraOrientation, Qt.vector3d(0,0,1) )
            camera.position = control.cameraPose
            camera.upVector = tools.move( Qt.vector3d(0,0,0), control.cameraOrientation, Qt.vector3d(0,1,0) )
        }


        QQ2.Connections{
            target: control
            onCameraPoseChanged:{
                camera.updatePose()

                /*camera.position = control.cameraPose
                camera.viewCenter = tools.move( camera.position, control.cameraOrientation, Qt.vector3d(0,0,1) )
                camera.upVector = tools.move( Qt.vector3d(0,0,0), control.cameraOrientation, Qt.vector3d(0,1,0) )*/
                //camera.position = tools.move( control.cameraPose, control.cameraOrientation, Qt.vector3d(0,0,0.5) )
                //camera.viewCenter = tools.move( camera.position, control.cameraOrientation, Qt.vector3d(0,0,-2) ) //Qt.vector3d(cameraPose.x,cameraPose.y,cameraPose.z-2)
                //camera.upVector = Qt.vector3d(0.0, 1.0, 0.0)
            }
            onCameraOrientationChanged:{
                camera.updatePose()

                /*camera.position = control.cameraPose
                camera.viewCenter = tools.move( camera.position, control.cameraOrientation, Qt.vector3d(0,0,1) )
                camera.upVector = tools.move( Qt.vector3d(0,0,0), control.cameraOrientation, Qt.vector3d(0,1,0) )*/
                //camera.position = tools.move( control.cameraPose, control.cameraOrientation, Qt.vector3d(0,0,0.5) )
                //camera.viewCenter = tools.move( camera.position, control.cameraOrientation, Qt.vector3d(0,0,-2) ) //Qt.vector3d(cameraPose.x,cameraPose.y,cameraPose.z-2)
                //camera.upVector = Qt.vector3d(0.0, 1.0, 0.0)
            }
        }
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                id: renderer
                camera: camera
                //clearColor: Qt.rgba(0.0, 0.4, 0.7, 1.0)
                frustumCulling: false
                clearColor: "transparent" //Qt.rgba(0.0, 0.0, 0.0, 0.5)

                viewportRect: Qt.rect(0,0,1,1)
            }
        },
        InputSettings { }
    ]


    Entity {
        components: [
            PointLight {
                enabled: parent.enabled
                color: "black"
                intensity: 0
            },
            EnvironmentLight {
                enabled: parent.enabled

                irradiance: TextureLoader {
                    source: "qrc:/cedar-bridge/cedar_bridge_irradiance.dds"
                    wrapMode {
                        x: WrapMode.ClampToEdge
                        y: WrapMode.ClampToEdge
                    }
                    generateMipMaps: false
                }
                specular: TextureLoader {
                    source: "qrc:/cedar-bridge/cedar_bridge_specular.dds"
                    wrapMode {
                        x: WrapMode.ClampToEdge
                        y: WrapMode.ClampToEdge
                    }
                    generateMipMaps: false
                }
            }
        ]
    }

    /*Entity {
        components: [
            PointLight {
                color: "white"
                intensity: 1.0
                constantAttenuation: 1.0
                linearAttenuation: 0.0
                quadraticAttenuation: 0.0025
            },
            Transform {
                translation: Qt.vector3d(0.0, 0.0, 0.0)
            }
        ]
    }*/    

	Path3D{
        enabled: !control.arReady
        path: control.arPlan
    }

    Robot{
        scale: 0.0025
    }
}
