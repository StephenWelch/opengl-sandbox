#version 330 core
out vec4 fragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform float divider;

void main() {
    fragColor = texture(ourTexture, texCoord) * vec4(ourColor * divider, 1.0);
}