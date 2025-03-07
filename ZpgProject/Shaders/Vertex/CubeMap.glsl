#version 400
layout(location = 0) in vec3 position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 texCoord;

void main () {
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(position, 1.0);
	texCoord = position;
}
