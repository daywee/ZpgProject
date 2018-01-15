#version 400
 
 
in vec2 texCoord;
uniform sampler2D myTexture;
 
out vec4 frag_colour;
 
const vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
 
void main () {
  frag_colour = ambient + texture(myTexture, texCoord);
}
