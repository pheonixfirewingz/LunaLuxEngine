//
// Created by luket on 05/04/2020.
//

#ifndef LUNALUXENGINE_ISHADERLAYOUT_H
#define LUNALUXENGINE_ISHADERLAYOUT_H
#include <GLM/glm.hpp>

enum class Data_Type
{
    FLOAT_TYPE = 0,
    DOUBLE_TYPE = 1,
    INT_TYPE = 2,
    UINT_TYPE = 3,
};

struct Shader_Layout
{

};

class IShaderLayout
{
protected:
    virtual int getUninform(char* name) = 0;
    //uniform
    virtual void setUniform4(size_t,int,glm::vec4,Data_Type) = 0; 
    virtual void setUniform3(size_t,int,glm::vec3,Data_Type) = 0; 
    virtual void setUniform2(size_t,int,glm::vec2,Data_Type) = 0;
    //uniform_v
    virtual void setUniformv4(size_t,int,glm::vec4,Data_Type) = 0;
public:
    void createShaderLayout(Shader_Layout&);
};

#endif //LUNALUXENGINE_ISHADERLAYOUT_H
