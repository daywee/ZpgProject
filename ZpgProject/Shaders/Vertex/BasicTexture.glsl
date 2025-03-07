#version 400
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 coord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 worldPosition;
out vec3 worldNormal;
out vec2 texCoord;

void main () {
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (position, 1.0);
	worldPosition = modelMatrix * vec4(position, 1.0);
	worldNormal = transpose(inverse(mat3(modelMatrix))) * normal;
	texCoord = coord;
}
