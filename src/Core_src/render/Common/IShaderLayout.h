//
// Created by luket on 05/04/2020.
//

#ifndef LUNALUXENGINE_ISHADERLAYOUT_H
#define LUNALUXENGINE_ISHADERLAYOUT_H
#include <stdint.h>

struct ShaderLayout
{

};

class IShaderLayout
{
private:
    virtual int getUninform(char* name) = 0;
    //uniform
    virtual void setUniform(size_t,int,float,float,float,float) = 0;
    virtual void setUniform(size_t,int,int,int,int,int) = 0;
    virtual void setUniform(size_t,int,unsigned int,unsigned int,unsigned int,unsigned int) = 0;
    //uniform_v
    virtual void setUniformv(size_t,int,float,float,float,float) = 0;
    virtual void setUniformv(size_t,int,int,int,int,int) = 0;
    virtual void setUniformv(size_t,int,unsigned int,unsigned int,unsigned int,unsigned int) = 0;
public:
    void createShaderLayout(ShaderLayout&);
};

#endif //LUNALUXENGINE_ISHADERLAYOUT_H
