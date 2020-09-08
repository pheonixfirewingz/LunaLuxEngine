//
// Created by luket on 17/08/2020.
//

#include "OpenGLUtils.h"

namespace LunaLuxEngine
{
    [[maybe_unused]] void LunaLuxEngine::OpenGLUtils::setBool(unsigned int shaderid, const std::string &name, bool value)
    {
        glUniform1i(glGetUniformLocation(shaderid, name.c_str()), (int) value);
    }

    [[maybe_unused]] void LunaLuxEngine::OpenGLUtils::setInt(unsigned int shaderid, const std::string &name, int value)
    {
        glUniform1i(glGetUniformLocation(shaderid, name.c_str()), value);
    }

    [[maybe_unused]] void LunaLuxEngine::OpenGLUtils::setFloat(unsigned int shaderid, const std::string &name, float value)
    {
        glUniform1f(glGetUniformLocation(shaderid, name.c_str()), value);
    }

    [[maybe_unused]] void OpenGLUtils::setDouble(unsigned int shaderid, const std::string &name, double value)
    {
        glUniform1d(glGetUniformLocation(shaderid, name.c_str()), value);
    }

    [[maybe_unused]] void LunaLuxEngine::OpenGLUtils::setVec2(unsigned int shaderid, const std::string &name, float x, float y)
    {
        glUniform2f(glGetUniformLocation(shaderid, name.c_str()), x, y);
    }

    [[maybe_unused]] void LunaLuxEngine::OpenGLUtils::setVec3(unsigned int shaderid, const std::string &name, float x, float y, float z)
    {
        glUniform3f(glGetUniformLocation(shaderid, name.c_str()), x, y, z);
    }

    [[maybe_unused]] void LunaLuxEngine::OpenGLUtils::setVec4(unsigned int shaderid, const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(shaderid, name.c_str()), x, y, z, w);
    }

    [[maybe_unused]] void OpenGLUtils::setVec2(unsigned int shaderid, const std::string &name, vec2f vec)
    {
        glUniform2f(glGetUniformLocation(shaderid, name.c_str()), vec.getX(), vec.getY());
    }

    [[maybe_unused]] void OpenGLUtils::setVec3(unsigned int shaderid, const std::string &name, vec3f vec)
    {
        glUniform3f(glGetUniformLocation(shaderid, name.c_str()), vec.getX(), vec.getY(), vec.getZ());
    }

    [[maybe_unused]] void OpenGLUtils::setVec4(unsigned int shaderid, const std::string &name, vec4f vec)
    {
        glUniform4f(glGetUniformLocation(shaderid, name.c_str()), vec.getX(), vec.getY(), vec.getZ(), vec.getW());
    }

    [[maybe_unused]] void OpenGLUtils::setVec2(unsigned int shaderid, const std::string &name, vec2d vec)
    {
        glUniform2d(glGetUniformLocation(shaderid, name.c_str()), vec.getX(), vec.getY());
    }

    [[maybe_unused]] void OpenGLUtils::setVec3(unsigned int shaderid, const std::string &name, vec3d vec)
    {
        glUniform3d(glGetUniformLocation(shaderid, name.c_str()), vec.getX(), vec.getY(), vec.getZ());
    }

    [[maybe_unused]] void OpenGLUtils::setVec4(unsigned int shaderid, const std::string &name, vec4d vec)
    {
        glUniform4d(glGetUniformLocation(shaderid, name.c_str()), vec.getX(), vec.getY(), vec.getZ(), vec.getW());
    }

    [[maybe_unused]] void LunaLuxEngine::OpenGLUtils::setMat2(unsigned int shaderid, const std::string &name, const glm::mat2 &mat)
    {
        glUniformMatrix2fv(glGetUniformLocation(shaderid, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    [[maybe_unused]] void LunaLuxEngine::OpenGLUtils::setMat3(unsigned int shaderid, const std::string &name, const glm::mat3 &mat)
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderid, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    [[maybe_unused]] void LunaLuxEngine::OpenGLUtils::setMat4(unsigned int shaderid, const std::string &name, const glm::mat4 &mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderid, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}