#version 400
in vec3 vp;

uniform mat4 trasfromMatrix;

void main () {
  gl_Position = trasfromMatrix * vec4 (vp, 1.0);
}
