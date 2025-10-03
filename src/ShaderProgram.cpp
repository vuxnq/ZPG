#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const std::vector<ref<Shader>>& shaders) {
	id = glCreateProgram();

	for (auto& shader : shaders) {
		shader->Attach(id);
	}

	glLinkProgram(id);

	GLint status;
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}
}

void ShaderProgram::Use() {
    glUseProgram(id);
}

void ShaderProgram::UnUse() {
    glUseProgram(0);
}

int ShaderProgram::GetUniformLocation(const std::string& name) {
	GLint location;
	if (location = glGetUniformLocation(id, name.c_str()) == -1) {
		fprintf(stderr, "Uniform '%s' not found\n", name.c_str());
		exit(EXIT_FAILURE);
	}
	return location;
	// TODO: add cache
}

void ShaderProgram::SetUniform(const std::string& name, const glm::mat4& value) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
