#version 330 core
out vec4 fragColor;
in vec3 ourColor;

uniform float divider;

void main() {
    fragColor = vec4(ourColor / divider, 1.0);
}