#version 400

in vec4 worldPosition;
in vec3 worldNormal;
uniform vec3 worldLightPosition;
uniform vec3 worldCameraPosition;

out vec4 frag_colour;

const vec4 diffuseColor = vec4(0.385, 0.647, 0.812, 1.0);
const vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
const vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);

void main () {
	vec3 normal = normalize(worldNormal);
	vec3 lightDirection = normalize(worldLightPosition - vec3(worldPosition));
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	vec3 viewDirection = normalize(worldCameraPosition - vec3(worldPosition));

	float lambertian = max(dot(lightDirection, normal), 0.0);
	float specular = 0.0;
	
	if (lambertian > 0.0) {
		float specularAngle = max(dot(reflectionDirection, viewDirection), 0.0);
		specular = pow(specularAngle, 40.0);
	}

	frag_colour = ambient + lambertian * diffuseColor + specular * specularColor;
}
