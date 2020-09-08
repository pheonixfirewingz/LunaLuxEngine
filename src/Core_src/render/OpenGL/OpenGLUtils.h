//
// Created by luket on 17/08/2020.
//

#ifndef LUNALUXENGINE_OPENGLUTILS_H
#define LUNALUXENGINE_OPENGLUTILS_H

#include <GLM/glm.hpp>
#include "../../math/LLE_Vector.h"
#include "glad.h"
#include <string>

namespace LunaLuxEngine
{

    class OpenGLUtils
    {
    public:
        [[maybe_unused]] static void setBool(unsigned int shaderid, const std::string &name, bool value);

        [[maybe_unused]] static void setInt(unsigned int shaderid, const std::string &name, int value);

        [[maybe_unused]] static void setFloat(unsigned int shaderid, const std::string &name, float value);

        [[maybe_unused]] static void setDouble(unsigned int shaderid, const std::string &name, double value);

        [[maybe_unused]] static void setVec2(unsigned int shaderid, const std::string &name, float x, float y);

        [[maybe_unused]] static void setVec3(unsigned int shaderid, const std::string &name, float x, float y, float z);

        [[maybe_unused]] static void setVec4(unsigned int shaderid, const std::string &name, float x, float y, float z, float w);

        [[maybe_unused]] static void setVec2(unsigned int shaderid, const std::string &name, vec2f);

        [[maybe_unused]] static void setVec3(unsigned int shaderid, const std::string &name, vec3f);

        [[maybe_unused]] static void setVec4(unsigned int shaderid, const std::string &name, vec4f);

        [[maybe_unused]] static void setVec2(unsigned int shaderid, const std::string &name, vec2d);

        [[maybe_unused]] static void setVec3(unsigned int shaderid, const std::string &name, vec3d);

        [[maybe_unused]] static void setVec4(unsigned int shaderid, const std::string &name, vec4d);

        [[maybe_unused]] static void setMat2(unsigned int shaderid, const std::string &name, const glm::mat2 &mat);

        [[maybe_unused]] static void setMat3(unsigned int shaderid, const std::string &name, const glm::mat3 &mat);

        [[maybe_unused]] static void setMat4(unsigned int shaderid, const std::string &name, const glm::mat4 &mat);
    };

}
#endif //LUNALUXENGINE_OPENGLUTILS_H
