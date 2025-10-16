#include "core/ShaderProgram.h"
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

void ShaderProgram::SetUniform(const std::string& name, float value) {
	glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform(const std::string& name, int value) {
	glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform(const std::string& name, const glm::vec2& value) {
	glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string& name, const glm::vec3& value) {
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string& name, const glm::vec4& value) {
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string& name, const glm::mat2& value) {
	glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string& name, const glm::mat3& value) {
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string& name, const glm::mat4& value) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

int ShaderProgram::GetUniformLocation(const std::string& name) {
	GLint location;
	if ((location = glGetUniformLocation(id, name.c_str())) == -1) {
		fprintf(stderr, "Uniform '%s' not found\n", name.c_str());
		exit(EXIT_FAILURE);
	}
	return location;
	// TODO: add cache
}

void ShaderProgram::OnNotify(const Event& event) {
	switch (event.type) {
		case EventType::CameraPositionChanged: {
			auto payload = (CameraPositionChangedPayload*)event.payload;
			Use();
			SetUniform("viewMatrix", payload->viewMatrix);
			SetUniform("projMatrix", payload->projectionMatrix);
			break;
		}
		case EventType::PointLightSet: {
			auto payload = (PointLightSetPayload*)event.payload;
			Use();
			SetUniform("pointLights[" + std::to_string(lightcount) + "].color", payload->color);
			SetUniform("pointLights[" + std::to_string(lightcount) + "].position", payload->position);
			lightcount++;
			break;
		}
		default:
			break;
	}
}