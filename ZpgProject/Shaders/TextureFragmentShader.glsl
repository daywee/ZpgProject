#version 400

in vec2 texCoord;
uniform sampler2D myTexture;
out vec4 frag_colour;

void main () {
	frag_colour = texture(myTexture, texCoord);
}
