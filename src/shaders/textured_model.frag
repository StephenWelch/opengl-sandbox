#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D textureA;
uniform sampler2D textureB;

void main() {
	fragColor = mix(texture(textureA, texCoord), texture(textureB, texCoord), 0.2);
}