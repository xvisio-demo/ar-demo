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
