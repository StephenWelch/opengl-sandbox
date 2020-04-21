
#include "Shader.h"

#include "util/util.h"

bool Shader::shaderCompiledSuccessfully(const GLuint& shaderId) const
{
		int success;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

		return success==GL_TRUE;
}

std::string Shader::getShaderCompilationErrors(const GLuint& shaderId) const
{
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
		return std::string(infoLog);
}

bool Shader::programLinkedSuccessfully(const GLuint& programId) const
{
		int success;
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		return success==GL_TRUE;
}

std::string Shader::getProgramLinkErrors(const GLuint& programId) const
{
		char infoLog[512];
		glGetProgramInfoLog(programId, 512, nullptr, infoLog);
		return std::string(infoLog);
}

void Shader::init()
{
		GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertexSource = util::getFileAsString(vertexPath);
		std::string fragmentSource = util::getFileAsString(fragmentPath);
		const GLchar* vertexSource_cstr = vertexSource.c_str();
		const GLchar* fragmentSource_cstr = fragmentSource.c_str();

		glShaderSource(vertexId, 1, &vertexSource_cstr, nullptr);
		glShaderSource(fragmentId, 1, &fragmentSource_cstr, nullptr);

		glCompileShader(vertexId);
		glCompileShader(fragmentId);

		ENGINE_ASSERT(shaderCompiledSuccessfully(vertexId),
						"Error compiling shader {}:\n{}", vertexPath,
						getShaderCompilationErrors(vertexId));
		ENGINE_ASSERT(shaderCompiledSuccessfully(fragmentId),
						"Error compiling shader {}:\n{}", fragmentPath,
						getShaderCompilationErrors(fragmentId));

		programId = glCreateProgram();
		glAttachShader(programId, vertexId);
		glAttachShader(programId, fragmentId);
		glLinkProgram(programId);

		ENGINE_ASSERT(programLinkedSuccessfully(programId),
						"Error linking shader program:\n{}",
						getProgramLinkErrors(programId));

		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
}

void Shader::use() { glUseProgram(programId); }

void Shader::cleanup() { glDeleteProgram(programId); }

void Shader::setBindingPoint(const std::string& name,
				const GLuint& bindingIndex)
{
		GLuint uniformIndex = glGetUniformBlockIndex(programId, name.c_str());
		glUniformBlockBinding(programId, uniformIndex, bindingIndex);
}

// Wrapper functions for uniforms taken from
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
void Shader::setBool(const std::string& name, bool value) const
{
		glUniform1i(getUniformLocation(name), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
		glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
		glUniform1f(getUniformLocation(name), value);
}

void Shader::setFloat3(const std::string& name, const glm::vec3 value) const
{
		glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setFloat4(const std::string& name, const glm::vec4 value) const
{
		glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
		glUniform2fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
		glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
		glUniform3fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
		glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
		glUniform4fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z,
				float w)
{
		glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
		glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
		glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

GLint Shader::getUniformLocation(std::string name) const
{
		GLint location = glGetUniformLocation(programId, name.c_str());

		ENGINE_ASSERT(location!=-1, "Uniform {} does not exist.", name);

		return location;
}
