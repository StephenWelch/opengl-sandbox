#version 330 core
out vec4 fragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D ourTextureA;
uniform sampler2D ourTextureB;
uniform float divider;

void main() {
    fragColor = mix(texture(ourTextureA, texCoord) * vec4(ourColor * divider, 1.0), texture(ourTextureB, texCoord) * vec4(ourColor * divider, 1.0), 0.2);
//	fragColor = mix(texture(ourTextureA, texCoord), texture(ourTextureB, texCoord), 0.2);
}