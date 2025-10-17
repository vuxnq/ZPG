#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "core/ShaderProgram.h"

class ShaderProgramManager {
public:
    ShaderProgramManager() {}
    ~ShaderProgramManager() {}

    void AddShaderProgram(const std::string& name, const ref<ShaderProgram>& shaderProgram);

    const ref<ShaderProgram>& GetShaderProgram(const std::string& name);
    const std::map<std::string, ref<ShaderProgram>>& GetShaderPrograms() { return shaderPrograms; }

private:
    std::map<std::string, ref<ShaderProgram>> shaderPrograms;
};
