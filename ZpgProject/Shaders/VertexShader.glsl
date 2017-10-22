#version 400
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec4 worldPosition;
out vec4 worldNormal;

void main () {
  gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (position, 1.0);
  worldPosition = modelMatrix * vec4(position, 1.0);
  worldNormal = modelMatrix * vec4(normal, 1.0);
}
