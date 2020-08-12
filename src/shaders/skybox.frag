#version 330 core
out vec4 oFragColor;

in vec3 iTexCoord;

uniform samplerCube skybox;

void main()
{
    oFragColor = vec4(skybox, iTexCoord);
}