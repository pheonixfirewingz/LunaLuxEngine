//
// Created by luket on 17/08/2020.
//

#ifndef LUNALUXENGINE_OPENGLUTILS_H
#define LUNALUXENGINE_OPENGLUTILS_H
#include <GLM/glm.hpp>
#include "glad.h"
#include <string>

namespace LunaLuxEngine
{

    class OpenGLUtils
    {
    public:
        static void setBool(int shaderid,const std::string &name, bool value);
        static void setInt(int shaderid,const std::string &name, int value);
        static void setFloat(int shaderid,const std::string &name, float value);
        static void setVec2(int shaderid,const std::string &name, float x, float y);
        static void setVec3(int shaderid,const std::string &name, float x, float y, float z);
        static void setVec4(int shaderid,const std::string &name, float x, float y, float z, float w);
        static void setMat2(int shaderid,const std::string &name, const glm::mat2 &mat);
        static void setMat3(int shaderid,const std::string &name, const glm::mat3 &mat);
        static void setMat4(int shaderid,const std::string &name, const glm::mat4 &mat);
    };

}
#endif //LUNALUXENGINE_OPENGLUTILS_H
