#include "shader/Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& shaderSourcePath, GLenum shaderType) {
    std::string source = ReadShaderSource(shaderSourcePath);
	const GLchar* sourcePtr = source.data();

    id = glCreateShader(shaderType);
	glShaderSource(id, 1, &sourcePtr, NULL);
    glCompileShader(id);

    GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Shader compilation failure %s: %s\n", shaderSourcePath.c_str(), strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}
}

void Shader::Attach(GLuint programId) {
	glAttachShader(programId, id);
}

std::string Shader::ReadShaderSource(const std::string& shaderSourcePath) {
    std::ifstream file(shaderSourcePath);
    if (!file.is_open()) {
        fprintf(stderr, "Failed to read shader file: %s\n", shaderSourcePath.c_str());
        exit(EXIT_FAILURE);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    std::string content = ss.str();

    return std::move(content);
}
