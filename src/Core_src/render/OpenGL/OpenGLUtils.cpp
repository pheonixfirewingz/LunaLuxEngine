//
// Created by luket on 17/08/2020.
//

#include "OpenGLUtils.h"

namespace LunaLuxEngine
{
    void LunaLuxEngine::OpenGLUtils::setBool(int shaderid,const std::string &name, bool value)
    {
        glUniform1i(glGetUniformLocation(shaderid, name.c_str()), (int)value);
    }
    void LunaLuxEngine::OpenGLUtils::setInt(int shaderid,const std::string &name, int value)
    {
        glUniform1i(glGetUniformLocation(shaderid, name.c_str()), value);
    }
    void LunaLuxEngine::OpenGLUtils::setFloat(int shaderid,const std::string &name, float value)
    {
        glUniform1f(glGetUniformLocation(shaderid, name.c_str()), value);
    }
    void LunaLuxEngine::OpenGLUtils::setVec2(int shaderid,const std::string &name, float x, float y)
    {
        glUniform2f(glGetUniformLocation(shaderid, name.c_str()), x, y);
    }
    void LunaLuxEngine::OpenGLUtils::setVec3(int shaderid,const std::string &name, float x, float y, float z)
    {
        glUniform3f(glGetUniformLocation(shaderid, name.c_str()), x, y, z);
    }
    void LunaLuxEngine::OpenGLUtils::setVec4(int shaderid,const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(shaderid, name.c_str()), x, y, z, w);
    }
    void LunaLuxEngine::OpenGLUtils::setMat2(int shaderid,const std::string &name, const glm::mat2 &mat)
    {
        glUniformMatrix2fv(glGetUniformLocation(shaderid, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void LunaLuxEngine::OpenGLUtils::setMat3(int shaderid,const std::string &name, const glm::mat3 &mat)
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderid, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void LunaLuxEngine::OpenGLUtils::setMat4(int shaderid,const std::string &name, const glm::mat4 &mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderid, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}