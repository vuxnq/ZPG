#include "ShaderProgramManager.h"

void ShaderProgramManager::AddShaderProgram(const std::string& name, const ref<ShaderProgram>& shaderProgram) {
    shaderPrograms[name] = shaderProgram;
}

const ref<ShaderProgram>& ShaderProgramManager::GetShaderProgram(const std::string& name) {
    if (!shaderPrograms.contains(name)) {
        fprintf(stderr, "ShaderProgram '%s' does not exist\n", name.c_str());
        exit(EXIT_FAILURE);
    }
    return shaderPrograms[name];
}