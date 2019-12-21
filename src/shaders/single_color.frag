#version 330 core
out vec4 fragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D textureA;
uniform sampler2D textureB;
uniform float divider;

void main() {
    fragColor = mix(texture(textureA, texCoord) * vec4(color * divider, 1.0), texture(textureB, texCoord) * vec4(color * divider, 1.0), 0.2);
//	fragColor = mix(texture(textureA, texCoord), texture(textureB, texCoord), 0.2);
}