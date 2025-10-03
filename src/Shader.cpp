#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& shaderSourcePath, GLenum shaderType) {
	const GLchar* source = ReadShaderSource(shaderSourcePath).c_str();

    id = glCreateShader(shaderType);
	glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
}

std::string Shader::ReadShaderSource(const std::string& shaderSourcePath) {
    std::ifstream file(shaderSourcePath);
    if (!file.is_open()) {
        std::cerr << "Failed to read shader file: " << shaderSourcePath << std::endl;
        exit(EXIT_FAILURE);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    std::string content = ss.str();

    return std::move(content);
}
