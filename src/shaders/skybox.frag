#version 330 core

out vec4 oFragColor;

in vec3 iTexCoord;

uniform samplerCube uSkybox;

void main()
{
    oFragColor = texture(uSkybox, iTexCoord);
}