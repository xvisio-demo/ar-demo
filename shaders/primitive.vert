#version 150 core

in vec3 vertexPosition;
in vec3 vertexNormal;

out vec4 positionInLightSpace;
out vec3 position;
out vec3 normal;

uniform mat4 lightViewProjection;
uniform mat4 modelMatrix;
uniform mat4 modelView;
uniform mat3 modelViewNormal;
uniform mat4 mvp;

void main() {
    position = vertexPosition;
    gl_Position = mvp * vec4( vertexPosition, 1.0 );
}
