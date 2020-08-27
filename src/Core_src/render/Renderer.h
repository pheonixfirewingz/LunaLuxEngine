#ifndef LUNALUXENGINE_RENDERER_H
#define LUNALUXENGINE_RENDERER_H

#include "Common/IRender.h"
#include "Buffer.h"
#include "Shader.h"
#include "OpenGL/OpenGLTexture.h"
#include "ShaderLayout.h"

namespace LunaLuxEngine
{
    class Renderer
    {
    private:
        Renderer();

        IRender *render;
        VertexBuffer *vbuffer;
        IndexBuffer *ibuffer;
        Shader *shader;
        ShaderLayout *layout;
        OpenGLTexture *texture;
    public:
        inline static Renderer &get()
        {
            static Renderer *rend = new Renderer();
            return *rend;
        }

        void initRender();

        void preRender();

        void Render();
    };
}
#endif