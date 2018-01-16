#version 400

struct Light {
	vec3 position;
};

const int MAX_LIGHTS = 10;

uniform Light lights[MAX_LIGHTS];
uniform int lightsCount;

in vec4 worldPosition;
in vec3 worldNormal;
uniform vec3 worldLightPosition;
uniform vec3 worldCameraPosition;

in vec2 texCoord;
uniform sampler2D myTexture;

out vec4 frag_colour;

const vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
const vec3 specularColor = vec3(1.0, 1.0, 1.0);

void main () {
	vec3 normal = normalize(worldNormal);
	vec3 viewDirection = normalize(worldCameraPosition - vec3(worldPosition));

	vec3 light = vec3(0.);
	for (int i = 0; i < lightsCount; i++) {
		vec3 lightDirection = normalize(lights[i].position - vec3(worldPosition));
		vec3 reflectionDirection = reflect(-lightDirection, normal);

		float lambertian = max(dot(lightDirection, normal), 0.0);
		float specular = 0.0;
	
		if (lambertian > 0.0) {
			float specularAngle = max(dot(reflectionDirection, viewDirection), 0.0);
			specular = pow(specularAngle, 40.0);
		}

		light += lambertian * vec3(texture(myTexture, texCoord)) + specular * specularColor;
	}
	
	frag_colour = ambient + vec4(light, 1.);
}
