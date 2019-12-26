#version 330 core

struct Material {
	vec3 ambientStrength;
	vec3 diffuseStrength;
	vec3 specularStrength;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambientIntensity;
	vec3 diffuseIntensity;
	vec3 specularIntensity;
};

out vec4 oFragColor;

in vec2 iTexCoord;
in vec3 iNormal;
in vec3 iFragPos;

uniform sampler2D uTexture;
uniform vec3 uViewPos;

uniform Light uLight;
uniform Material uMaterial;

void main() {
	vec3 normal = normalize(iNormal);
	vec3 lightDirection = normalize(uLight.position - iFragPos);
	vec3 viewDirection = normalize(uViewPos - iFragPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);

	vec3 ambientLightColor = uMaterial.ambientStrength * uLight.ambientIntensity;
	float diffuseScalar = max(0.0, dot(normal, lightDirection));
	vec3 diffuseColor = uLight.diffuseIntensity * (diffuseScalar * uMaterial.diffuseStrength);
	float specularScalar = pow(max(0.0, dot(viewDirection, reflectDirection)), uMaterial.shininess);
	vec3 specularColor = uLight.specularIntensity * uMaterial.specularStrength * specularScalar;

	oFragColor = vec4(ambientLightColor + diffuseColor + specularColor, 1.0) * texture(uTexture, iTexCoord);
}