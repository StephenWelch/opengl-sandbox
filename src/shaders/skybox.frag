#version 330 core
out vec4 FragColor;

in vec3 iNormal;
in vec3 iFragPo;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
    vec3 I = normalize(iFragPos - cameraPos);
    vec3 R = reflect(I, normalize(iNormal));
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}