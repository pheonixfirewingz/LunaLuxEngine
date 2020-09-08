//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_OPENGL_H
#define LUNALUXENGINE_OPENGL_H

#include "../Renderer.h"
#include "../Buffer.h"
#include "../Shader.h"
#include "../../render/Common/IRender.h"
#include "glad.h"

namespace LunaLuxEngine
{
    class OGLRenderer : public IRender
    {
    private:
        GLuint VertexArrayID;
    public:
        OGLRenderer();

        ~OGLRenderer();

        void clearscreen(float[4]) override;

        void prepRender() override
        {};

        void fireRender(int) override;
    };
}
#endif
