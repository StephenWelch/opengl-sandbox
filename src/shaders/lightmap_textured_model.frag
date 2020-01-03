#version 330 core

#define MAX_DIRECTIONAL_LIGHTS 100
#define MAX_POINT_LIGHTS 100
#define NUM_SPOTLIGHTS 100

struct Material {
	sampler2D diffuseTexture;
	sampler2D specularTexture;
	sampler2D emissiveTexture;
	float shininess;
};

struct DirectionalLight {
	vec4 direction;

	vec4 ambientIntensity;
	vec4 diffuseIntensity;
	vec4 specularIntensity;
};

struct PointLight {
	vec4 position;

	vec4 ambientIntensity;
	vec4 diffuseIntensity;
	vec4 specularIntensity;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec4 position;
	vec4 direction;

	vec4 ambientIntensity;
	vec4 diffuseIntensity;
	vec4 specularIntensity;

	float constant;
	float linear;
	float quadratic;
	
	float cutOff;
	float outerCutOff;
};

layout (std140) uniform uDirectionalLights {
	DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
	int numDirectionalLights;
};

layout (std140) uniform uPointLights {
	PointLight pointLights[MAX_POINT_LIGHTS];
	int numPointLights;
};

layout (std140) uniform uSpotLights {
	SpotLight spotLights[NUM_SPOTLIGHTS];
	int numSpotLights;
};

out vec4 oFragColor;

in vec2 iTexCoord;
in vec3 iNormal;
in vec3 iFragPos;

uniform Material uMaterial;
uniform vec3 uViewPos;
uniform bool uEmissionsEnabled = false;

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDirection);

void main() {
	vec3 normal = normalize(iNormal);

	vec3 viewDirection = normalize(uViewPos - iFragPos);

	vec3 directionalLightColor;
	for(int i = 0; i < numDirectionalLights; i++) {
		directionalLightColor += calcDirectionalLight(directionalLights[i], normal, viewDirection);
	}
	vec3 pointLightColor;
	for(int i = 0; i < numPointLights; i++) {
		pointLightColor += calcPointLight(pointLights[i], normal, viewDirection);
	}
	vec3 spotLightColor;
	for(int i = 0; i < numSpotLights; i++) {
		spotLightColor += calcSpotLight(spotLights[i], normal, viewDirection);
	}
	vec3 emissionColor;
	if(uEmissionsEnabled) {
		emissionColor = texture(uMaterial.emissiveTexture, iTexCoord).rgb;
	}
	
	vec3 combinedLightingColor = directionalLightColor + pointLightColor + spotLightColor + emissionColor;

	oFragColor = vec4(combinedLightingColor, 1.0);
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDirection = normalize(-light.direction.xyz);
	vec3 reflectDirection = reflect(-lightDirection, normal);

	vec3 materialDiffuse = texture(uMaterial.diffuseTexture, iTexCoord).rgb;
	vec3 materialSpecular = texture(uMaterial.specularTexture, iTexCoord).rgb;

	vec3 ambientLightColor = light.ambientIntensity.rgb * materialDiffuse;

	float diffuseScalar = max(0.0, dot(normal, lightDirection));
	vec3 diffuseColor = light.diffuseIntensity.rgb * diffuseScalar * materialDiffuse;

	float specularScalar = pow(max(0.0, dot(viewDirection, reflectDirection)), uMaterial.shininess);
	vec3 specularColor = light.specularIntensity.rgb * specularScalar * materialSpecular;

	return ambientLightColor + diffuseColor + specularColor;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDirection = normalize(light.position.xyz - iFragPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);

	float lightDistance = length(light.position.xyz - iFragPos);
	float attenuation = 1.0 / ((light.constant) + (light.linear * lightDistance) + (light.quadratic * lightDistance * lightDistance));

	vec3 materialDiffuse = texture(uMaterial.diffuseTexture, iTexCoord).rgb;
	vec3 materialSpecular = texture(uMaterial.specularTexture, iTexCoord).rgb;

	vec3 ambientLightColor = attenuation * light.ambientIntensity.rgb * materialDiffuse;

	float diffuseScalar = max(0.0, dot(normal, lightDirection));
	vec3 diffuseColor = attenuation * light.diffuseIntensity.rgb * diffuseScalar * materialDiffuse;

	float specularScalar = pow(max(0.0, dot(viewDirection, reflectDirection)), uMaterial.shininess);
	vec3 specularColor = attenuation * light.specularIntensity.rgb * specularScalar * materialSpecular;

	return ambientLightColor + diffuseColor + specularColor;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDirection = normalize(light.position.xyz - iFragPos);
	float lightDistance = length(light.position.xyz - iFragPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);

	vec3 materialDiffuse = texture(uMaterial.diffuseTexture, iTexCoord).rgb;
	vec3 materialSpecular = texture(uMaterial.specularTexture, iTexCoord).rgb;

	float theta = dot(lightDirection, normalize(-light.direction.xyz));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	float attenuation = 1.0 / ((light.constant) + (light.linear * lightDistance) + (light.quadratic * lightDistance * lightDistance));

	vec3 ambientLightColor = attenuation* light.ambientIntensity.rgb * materialDiffuse;

	float diffuseScalar = max(0.0, dot(normal, lightDirection));
	vec3 diffuseColor = intensity * attenuation * light.diffuseIntensity.rgb * diffuseScalar * materialDiffuse;

	float specularScalar = pow(max(0.0, dot(viewDirection, reflectDirection)), uMaterial.shininess);
	vec3 specularColor = intensity * attenuation * light.specularIntensity.rgb * specularScalar * materialSpecular;

	return ambientLightColor + diffuseColor + specularColor;
}