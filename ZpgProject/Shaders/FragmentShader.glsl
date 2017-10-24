#version 400

in vec4 worldPosition;
in vec3 worldNormal;
uniform vec3 worldLightPosition;

out vec4 frag_colour;

void main () {
	vec3 lightVector = normalize(worldLightPosition - vec3(worldPosition));
	float dot_product = max(dot(vec4(lightVector, 1.0), normalize(vec4(worldNormal, 0.0))), 0.0);
	vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

	frag_colour = ambient + diffuse;
}
