#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 iTexCoord;
out vec3 iNormal;
out vec3 iFragPos;

uniform mat3 uNormalMatrix;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
	iTexCoord = vec2(aTexCoord.x, aTexCoord.y);
	iNormal = aNormal * uNormalMatrix;
	iFragPos = vec3(uModel * vec4(aPos, 1.0));
}