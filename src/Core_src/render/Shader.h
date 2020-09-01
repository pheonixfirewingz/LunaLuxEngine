#ifndef LUNALUXENGINE_SHADER_H
#define LUNALUXENGINE_SHADER_H

#include "Common/IShader.h"
#include "../LunaLuxEngineCore.h"

namespace LunaLuxEngine
{
    class Shader
    {
        unsigned int openGLshaderprogramid;
    private:
        IShader *Vshader;
        IShader *Fshader;
        void setup();
    public:
        Shader()
        {
            setup();
        }

        Shader(char *filedata, char *filedata1)
        {
            setup();
            compile(filedata,filedata1);
        }

        ~Shader();

        void compile(char*,char*);

        void use();

        void bind();

        void UnBind();

        unsigned int getOGLSID()
        {
            return openGLshaderprogramid;
        }
    };
}
#endif
