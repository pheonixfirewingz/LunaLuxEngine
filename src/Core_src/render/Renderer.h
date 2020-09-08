#ifndef LUNALUXENGINE_RENDERER_H
#define LUNALUXENGINE_RENDERER_H

#include "Common/IRender.h"
#include "Buffer.h"
#include "Shader.h"
#include "ShaderLayout.h"
#include "Texture.h"
#include "../common/entity/Camera.h"

namespace LunaLuxEngine
{
    class Renderer
    {
    private:
        IRender *render;
        float color[4] = {0.3f, 0.3f, 0.9f, 1.0f};
        Renderer();
    private:
        //         to be changed
        //------------------------------------------
        Buffer* buffer;
        Shader* shader;
        ShaderLayout* layout;
        Texture* texture;
        //----------------------------------------
    public:
        inline static Renderer &get()
        {
            static Renderer *rend = new Renderer();
            return *rend;
        }

        inline void setClearColour(float r,float g,float b,float a)
        {
            color[0] = r;
            color[1] = g;
            color[2] = b;
            color[3] = a;
        }

        void beginLevel(Camera&);
        void endLevel();

        void submit(Buffer* in_buffer,Shader* in_shader,std::vector<SHADERLAYOUTTYPE> in_types,Texture* in_texture)
        {
            buffer = in_buffer;
            shader = in_shader;
            layout = new ShaderLayout(in_types,in_buffer);
            texture = in_texture;
        }

        void preRender();

        void Render();
    };
}
#endif