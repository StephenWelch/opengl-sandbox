#version 330 core

struct Material {
	sampler2D diffuseTexture;
	sampler2D specularTexture;
	sampler2D emissionTexture;
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
uniform bool uEmissionsEnabled = false;

void main() {
	vec3 normal = normalize(iNormal);

	vec3 lightDirection = normalize(uLight.position - iFragPos);
	vec3 viewDirection = normalize(uViewPos - iFragPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);

	vec3 materialDiffuse = texture(uMaterial.diffuseTexture, iTexCoord).rgb;
	vec3 materialSpecular = texture(uMaterial.specularTexture, iTexCoord).rgb;

	vec3 ambientLightColor = uLight.ambientIntensity * materialDiffuse;

	float diffuseScalar = max(0.0, dot(normal, lightDirection));
	vec3 diffuseColor = uLight.diffuseIntensity * diffuseScalar * materialDiffuse;

	float specularScalar = pow(max(0.0, dot(viewDirection, reflectDirection)), uMaterial.shininess);
	vec3 specularColor = uLight.specularIntensity * specularScalar * materialSpecular;

	vec3 emissionColor;
	if(uEmissionsEnabled) {
		emissionColor = texture(uMaterial.emissionTexture, iTexCoord).rgb;
	}
	

	vec3 combinedLightingColor = ambientLightColor + diffuseColor + specularColor + emissionColor;

	oFragColor = vec4(combinedLightingColor, 1.0);
}