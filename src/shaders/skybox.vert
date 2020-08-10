#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 iNormal;
out vec3 iFragPos;

uniform mat3 uNormalMatrix;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    uNormal = mat3(transpose(inverse(uModel))) * aNormal;
    uFragPos = vec3(uModel * vec4(aPos, 1.0));
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}