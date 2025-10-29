#include "shader/ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "core/Camera.h"
#include "light/DirectionalLight.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"

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
	if (locationCache.contains(name))
		return locationCache[name];

	GLint location;
	if ((location = glGetUniformLocation(id, name.c_str())) == -1) {
		fprintf(stderr, "Uniform '%s' not found\n", name.c_str());
		// exit(EXIT_FAILURE);
	}

	locationCache[name] = location;
	return location;
}

void ShaderProgram::OnNotify(const Event& event) {
	if (event.type == EventType::CameraPositionChanged) {
		auto camera = (Camera*)event.payload;
		Use();
		SetUniform("viewMatrix", camera->GetViewMatrix());
		SetUniform("projMatrix", camera->GetProjMatrix());
		SetUniform("cameraPos", camera->GetPosition());
	} else if (event.type == EventType::AmbientLightSet) {
		auto color = *(glm::vec3*)event.payload;
		Use();
		SetUniform("ambient", color);
	} else if (event.type == EventType::DirectionalLightSet) {
		auto light = (DirectionalLight*)event.payload;
		Use();
		std::string base = "directionalLights[" + std::to_string(light->GetIndex()) + "].";
		SetUniform(base + "color", light->GetColor());
		SetUniform(base + "direction", light->GetDirection());
		SetUniform(base + "intensity", light->GetIntensity());
	} else if (event.type == EventType::DirectionalLightCountSet) {
		int count = (size_t)event.payload;
		Use();
		SetUniform("directionalLightCount", count);
	} else if (event.type == EventType::PointLightSet) {
		auto light = (PointLight*)event.payload;
		Use();
		std::string base = "pointLights[" + std::to_string(light->GetIndex()) + "].";
		SetUniform(base + "color", light->GetColor());
		SetUniform(base + "position", light->GetPosition());
		SetUniform(base + "intensity", light->GetIntensity());
	} else if (event.type == EventType::PointLightCountSet) {
		int count = (size_t)event.payload;
		Use();
		SetUniform("pointLightCount", count);
	} else if (event.type == EventType::SpotLightSet) {
		auto light = (SpotLight*)event.payload;
		Use();
		std::string base = "spotLights[" + std::to_string(light->GetIndex()) + "].";
		SetUniform(base + "color", light->GetColor());
		SetUniform(base + "position", light->GetPosition());
		SetUniform(base + "direction", light->GetDirection());
		SetUniform(base + "intensity", light->GetIntensity());
	} else if (event.type == EventType::SpotLightCountSet) {
		int count = (size_t)event.payload;
		Use();
		SetUniform("spotLightCount", count);
	}
}