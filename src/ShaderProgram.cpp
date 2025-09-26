#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) {
	const char* vertPtr = vertexShaderCode.c_str();
	const char* fragPtr = fragmentShaderCode.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertPtr, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragPtr, NULL);
    glCompileShader(fragmentShader);

	id = glCreateProgram();

	glAttachShader(id, fragmentShader);
	glAttachShader(id, vertexShader);
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
	}
}

void ShaderProgram::Use() {
    glUseProgram(id);
}

void ShaderProgram::UnUse() {
    glUseProgram(0);
}

std::string ReadShaderSource(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to read shader file: " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    std::string content = ss.str();

    return std::move(content);
}