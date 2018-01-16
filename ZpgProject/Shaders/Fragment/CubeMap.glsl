#version 400

in vec3 texCoord;
uniform samplerCube myTexture;

out vec4 frag_colour;

void main () {
	frag_colour = texture(myTexture, texCoord);
}
