#version 330 core
out vec4 oFragColor;

in vec2 iTexCoord;
in vec3 iNormal;
in vec3 iFragPos;

uniform sampler2D uTexture;
uniform vec3 uViewPos;

uniform vec3 uAmbientLightColor;
uniform vec3 uPositionalLightColor;

uniform float uAmbientLightStrength;
uniform float uPositionalLightStrength;

uniform float uSpecularStrength;
uniform float uShininess;

uniform vec3 uLightPos;


void main() {
	vec3 normal = normalize(iNormal);
	vec3 lightDirection = normalize(uLightPos - iFragPos);
	vec3 viewDirection = normalize(uViewPos - iFragPos);

	float diffuseScalar = max(0.0, dot(normal, lightDirection));
	vec3 diffuseColor = diffuseScalar * (uPositionalLightColor * uPositionalLightStrength);
	vec3 ambientLightColor = uAmbientLightStrength * uAmbientLightColor;
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularScalar = pow(max(0.0, dot(viewDirection, reflectDirection)), uShininess);
	vec3 specularColor = uSpecularStrength * uPositionalLightColor * specularScalar;

	oFragColor = vec4(ambientLightColor + diffuseColor + specularColor, 1.0) * texture(uTexture, iTexCoord);
}