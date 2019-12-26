#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D uTexture;
uniform vec3 uAmbientLightColor;
uniform float uAmbientLightStrength;

void main() {
	vec3 ambientLightColor = uAmbientLightStrength * uAmbientLightColor;
	fragColor = vec4(ambientLightColor, 1.0) * texture(uTexture, texCoord);
}