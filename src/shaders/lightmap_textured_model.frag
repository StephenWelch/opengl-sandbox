#version 330 core

struct Material {
	sampler2D diffuseTexture;
	sampler2D specularTexture;
	sampler2D emissiveTexture;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambientIntensity;
	vec3 diffuseIntensity;
	vec3 specularIntensity;
};

struct PointLight {
	vec3 position;

	vec3 ambientIntensity;
	vec3 diffuseIntensity;
	vec3 specularIntensity;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	vec3 ambientIntensity;
	vec3 diffuseIntensity;
	vec3 specularIntensity;

	float constant;
	float linear;
	float quadratic;
	
	float cutOff;
	float outerCutOff;
};

#define NUM_DIRECTIONAL_LIGHTS 1
#define NUM_POINT_LIGHTS 4
#define NUM_SPOTLIGHTS 1

out vec4 oFragColor;

in vec2 iTexCoord;
in vec3 iNormal;
in vec3 iFragPos;

uniform Material uMaterial;
uniform vec3 uViewPos;
uniform bool uEmissionsEnabled = false;

uniform DirectionalLight uDirectionalLights[NUM_DIRECTIONAL_LIGHTS];
uniform PointLight uPointLights[NUM_POINT_LIGHTS];
uniform SpotLight uSpotLights[NUM_SPOTLIGHTS];

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDirection);

void main() {
	vec3 normal = normalize(iNormal);

	vec3 viewDirection = normalize(uViewPos - iFragPos);

	vec3 directionalLightColor;
	for(int i = 0; i < NUM_DIRECTIONAL_LIGHTS; i++) {
		directionalLightColor += calcDirectionalLight(uDirectionalLights[i], normal, viewDirection);
	}
	vec3 pointLightColor;
	for(int i = 0; i < NUM_POINT_LIGHTS; i++) {
		pointLightColor += calcPointLight(uPointLights[i], normal, viewDirection);
	}
	vec3 spotLightColor;
	for(int i = 0; i < NUM_SPOTLIGHTS; i++) {
		spotLightColor += calcSpotLight(uSpotLights[i], normal, viewDirection);
	}
	vec3 emissionColor;
	if(uEmissionsEnabled) {
		emissionColor = texture(uMaterial.emissiveTexture, iTexCoord).rgb;
	}
	
	vec3 combinedLightingColor = directionalLightColor + pointLightColor + spotLightColor + emissionColor;

	oFragColor = vec4(combinedLightingColor, 1.0);
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDirection = normalize(-light.direction);
	vec3 reflectDirection = reflect(-lightDirection, normal);

	vec3 materialDiffuse = texture(uMaterial.diffuseTexture, iTexCoord).rgb;
	vec3 materialSpecular = texture(uMaterial.specularTexture, iTexCoord).rgb;

	vec3 ambientLightColor = light.ambientIntensity * materialDiffuse;

	float diffuseScalar = max(0.0, dot(normal, lightDirection));
	vec3 diffuseColor = light.diffuseIntensity * diffuseScalar * materialDiffuse;

	float specularScalar = pow(max(0.0, dot(viewDirection, reflectDirection)), uMaterial.shininess);
	vec3 specularColor = light.specularIntensity * specularScalar * materialSpecular;

	return ambientLightColor + diffuseColor + specularColor;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDirection = normalize(light.position - iFragPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);

	float lightDistance = length(light.position - iFragPos);
	float attenuation = 1.0 / ((light.constant) + (light.linear * lightDistance) + (light.quadratic * lightDistance * lightDistance));

	vec3 materialDiffuse = texture(uMaterial.diffuseTexture, iTexCoord).rgb;
	vec3 materialSpecular = texture(uMaterial.specularTexture, iTexCoord).rgb;

	vec3 ambientLightColor = attenuation * light.ambientIntensity * materialDiffuse;

	float diffuseScalar = max(0.0, dot(normal, lightDirection));
	vec3 diffuseColor = attenuation * light.diffuseIntensity * diffuseScalar * materialDiffuse;

	float specularScalar = pow(max(0.0, dot(viewDirection, reflectDirection)), uMaterial.shininess);
	vec3 specularColor = attenuation * light.specularIntensity * specularScalar * materialSpecular;

	return ambientLightColor + diffuseColor + specularColor;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDirection = normalize(light.position - iFragPos);
	float lightDistance = length(light.position - iFragPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);

	vec3 materialDiffuse = texture(uMaterial.diffuseTexture, iTexCoord).rgb;
	vec3 materialSpecular = texture(uMaterial.specularTexture, iTexCoord).rgb;

	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	float attenuation = 1.0 / ((light.constant) + (light.linear * lightDistance) + (light.quadratic * lightDistance * lightDistance));

	vec3 ambientLightColor = attenuation* light.ambientIntensity * materialDiffuse;

	float diffuseScalar = max(0.0, dot(normal, lightDirection));
	vec3 diffuseColor = intensity * attenuation * light.diffuseIntensity * diffuseScalar * materialDiffuse;

	float specularScalar = pow(max(0.0, dot(viewDirection, reflectDirection)), uMaterial.shininess);
	vec3 specularColor = intensity * attenuation * light.specularIntensity * specularScalar * materialSpecular;

	return ambientLightColor + diffuseColor + specularColor;
}