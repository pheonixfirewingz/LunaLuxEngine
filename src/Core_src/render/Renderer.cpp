#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"
#include <CrossWindow/WindowAPI.h>

static float vertex[] =
        {
                -0.5f, -0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
        };

int indices[] =
        {
                0, 1, 2,
                0, 2, 3,
        };

LunaLuxEngine::Renderer::Renderer()
{
    render = new OGLRenderer();
}

void LunaLuxEngine::Renderer::beginLevel()
{

}

void LunaLuxEngine::Renderer::endLevel()
{

}


void LunaLuxEngine::Renderer::initRender()
{
    LOG("Renderer::initRender() is deprecated");
	CWin.getNativeWindow()->fireResizeCallback();

    vbuffer.create(vertex, sizeof(vertex));
    ibuffer.create(indices, sizeof(indices));
    vbuffer.bind();
    //----------this is part of the layout abstract to be removed when complete--------------------
    glBindAttribLocation(1, 0, "position");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //---------------------------------------------------------------------------------------------------------s
    vbuffer.unBind();

    char* data = "#version 330 core\n"
                 "layout (location = 0) in vec3 position;\n"
                 "\n"
                 "out vec4 vertexColor;\n"
                 "float shift_factor = 0.0;\n"
                 "\n"
                 "void main()\n"
                 "{\n"
                 "    gl_Position = vec4(position, 1.0);\n"
                 "    vertexColor = vec4(position.x + shift_factor, position.y + shift_factor,0.0, 1.0);\n"
                 "}";
    char* data1 = "#version 330 core\n"
                  "out vec4 FragColor;\n"
                  "\n"
                  "in vec4 vertexColor;\n"
                  "\n"
                  "void main()\n"
                  "{\n"
                  "    FragColor = vertexColor;\n"
                  "}";

    shader.create();
    shader.compile(data, data1);
    shader.link();
};

float color[4] = { 0.3f, 0.3f, 0.9f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
	render->clearscreen(color);
	render->prepRender();
};

void LunaLuxEngine::Renderer::Render()
{
	vbuffer.bind();
	ibuffer.bind();
	render->fireRender(ibuffer.getIndexCount());
	vbuffer.unBind();
	ibuffer.unBind();
};

LunaLuxEngine::Renderer::~Renderer()
{
    ibuffer.destory();
    vbuffer.destory();
    render = nullptr;
}


