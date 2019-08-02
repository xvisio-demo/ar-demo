import Qt3D.Core 2.0
import Qt3D.Render 2.0

Effect {
    id: root

    parameters: [
        //Parameter { name: "lightIntensity"; value: root.light.lightIntensity },
    ]

    techniques: [
        Technique {
            filterKeys: [ FilterKey { name : "renderingStyle"; value : "forward" } ]

            graphicsApiFilter {
                api: GraphicsApiFilter.OpenGL
                profile: GraphicsApiFilter.CoreProfile
                majorVersion: 3
                minorVersion: 2
            }

            renderPasses: [
                RenderPass {
                    shaderProgram: ShaderProgram {
                        vertexShaderCode:   loadSource("qrc:/shaders/primitive.vert")
                        fragmentShaderCode: loadSource("qrc:/shaders/primitive.frag")
                    }
                    // no special render state set => use the default set of states
                }
            ]
        }
    ]
}
