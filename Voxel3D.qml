import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.12

import PointMesh 1.0

Entity {
    id: root

    property double size: 1.0
    property color color: "red"
    property alias effect: mat.effect
    property alias transform: transform

    property Material material:  PhongMaterial {
        id: mat
        ambient: root.color
        parameters: [
            Parameter { name: "color"; value: root.color },
            Parameter { name: "maincolor"; value: root.color }
        ]

        effect: Effect {

            //! [1]
            property string vertex: "qrc:/shaders/gl3/simpleColor.vert"
            property string fragment: "qrc:/shaders/gl3/simpleColor.frag"
            property string vertexES: "qrc:/shaders/es2/simpleColor.vert"
            property string fragmentES: "qrc:/shaders/es2/simpleColor.frag"
            //! [1]

            FilterKey {
                id: forward
                name: "renderingStyle"
                value: "forward"
            }

            //! [2]
            ShaderProgram {
                id: gl3Shader
                vertexShaderCode: loadSource(parent.vertex)
                fragmentShaderCode: loadSource(parent.fragment)
            }
            ShaderProgram {
                id: es2Shader
                vertexShaderCode: loadSource(parent.vertexES)
                fragmentShaderCode: loadSource(parent.fragmentES)
            }
            //! [2]

            techniques: [
                //! [3]
                // OpenGL 3.1
                Technique {
                    filterKeys: [forward]
                    graphicsApiFilter {
                        api: GraphicsApiFilter.OpenGL
                        profile: GraphicsApiFilter.CoreProfile
                        majorVersion: 3
                        minorVersion: 1
                    }
                    renderPasses: RenderPass {
                        shaderProgram: gl3Shader
                    }
                },
                //! [3]
                // OpenGL 2.0
                Technique {
                    filterKeys: [forward]
                    graphicsApiFilter {
                        api: GraphicsApiFilter.OpenGL
                        profile: GraphicsApiFilter.NoProfile
                        majorVersion: 2
                        minorVersion: 0
                    }
                    renderPasses: RenderPass {
                        shaderProgram: es2Shader
                    }
                },
                // ES 2.0
                Technique {
                    filterKeys: [forward]
                    graphicsApiFilter {
                        api: GraphicsApiFilter.OpenGLES
                        profile: GraphicsApiFilter.CoreProfile
                        majorVersion: 2
                        minorVersion: 0
                    }
                    renderPasses: RenderPass {
                        shaderProgram: es2Shader
                    }
                }
            ]
        }
    }

    CuboidMesh {
        id: mesh
        xExtent: root.size
        yExtent: root.size
        zExtent: root.size
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
