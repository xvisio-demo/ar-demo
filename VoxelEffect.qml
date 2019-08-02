import Qt3D.Core 2.0
import Qt3D.Render 2.0

Effect {
    id: root

    parameters: [
        Parameter { name: "color"; value: "red" }
    ]

    techniques: [
        Technique {
            filterKeys: [ FilterKey { name : "renderingStyle"; value : "forward" } ]
            //filterKeys: [ FilterKey { name : "pass"; value : "forward" } ]

            graphicsApiFilter {
                api: GraphicsApiFilter.OpenGL
                profile: GraphicsApiFilter.CoreProfile
                majorVersion: 3
                minorVersion: 2
            }

            renderPasses: [
                RenderPass {
                    shaderProgram: ShaderProgram {
                        vertexShaderCode:   loadSource("qrc:/shaders/voxel.vert")
                        fragmentShaderCode: loadSource("qrc:/shaders/voxel.frag")
                    }
                    // no special render state set => use the default set of states
                }
            ]
        },
        Technique {
            filterKeys: [ FilterKey { name : "renderingStyle"; value : "forward" } ]
            //filterKeys: [ FilterKey { name : "pass"; value : "forward" } ]

            graphicsApiFilter {
                api: GraphicsApiFilter.OpenGLES
                profile: GraphicsApiFilter.CoreProfile
                majorVersion: 2
                minorVersion: 0
            }

            renderPasses: [
                RenderPass {
                    shaderProgram: ShaderProgram {
                        vertexShaderCode:   loadSource("qrc:/shaders/voxel.es.vert")
                        fragmentShaderCode: loadSource("qrc:/shaders/voxel.es.frag")
                    }
                    // no special render state set => use the default set of states
                }
            ]
        }
    ]
}
