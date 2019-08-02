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


/*attribute vec4 qt_Vertex;
attribute vec4 qt_MultiTexCoord0;
uniform mat4 qt_ModelViewProjectionMatrix;
varying vec4 qt_TexCoord0;

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    qt_TexCoord0 = qt_MultiTexCoord0;
}*/
