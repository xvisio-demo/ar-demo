#version 150 core

uniform mat4 viewMatrix;
uniform vec3 color;

in vec3 position;
in vec3 normal;

out vec4 fragColor;

void main(void)
{
    fragColor = vec4(color.r, color.g, color.b, 1.0);
}


/*uniform sampler2D qt_Texture0;
varying vec4 qt_TexCoord0;

void main(void)
{
    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
}*/
