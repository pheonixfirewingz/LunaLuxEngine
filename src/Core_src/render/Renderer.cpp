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
    vbuffer = new VertexBuffer();
    ibuffer = new IndexBuffer();
    shader  = new Shader();
    texture = new OpenGLTexture("/home/digitech/Desktop/LunaLuxEngine/Disco-Dingo.jpg");
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
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

    vbuffer->create(vertex, sizeof(vertex));
    ibuffer->create(indices, sizeof(indices));
    vbuffer->bind();
    //----------this is part of the layout abstract to be removed when complete--------------------
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //---------------------------------------------------------------------------------------------------------s
    vbuffer->unBind();

    char* data = "#version 330 core\n"
                 "layout (location = 0) in vec3 aPos;\n"
                 "layout (location = 1) in vec3 aColor;\n"
                 "layout (location = 2) in vec2 aTexCoord;\n"
                 "\n"
                 "out vec3 ourColor;\n"
                 "out vec2 TexCoord;\n"
                 "\n"
                 "void main()\n"
                 "{\n"
                 "    gl_Position = vec4(aPos, 1.0);\n"
                 "    ourColor = aColor;\n"
                 "    TexCoord = aTexCoord;\n"
                 "}";
    char* data1 = "#version 330 core\n"
                  "out vec4 FragColor;\n"
                  "  \n"
                  "in vec3 ourColor;\n"
                  "in vec2 TexCoord;\n"
                  "\n"
                  "uniform sampler2D ourTexture;\n"
                  "\n"
                  "void main()\n"
                  "{\n"
                  "    FragColor = texture(ourTexture, TexCoord);\n"
                  "}";
    shader->compile(data, data1);

    /*shader->bind();
    glUniform1i(glGetUniformLocation(shader->getOGLSID(), "texture1"), 0);
    shader->UnBind();*/
}

float color[4] = { 0.3f, 0.3f, 0.9f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
	render->clearscreen(color);
	render->prepRender();
};

void LunaLuxEngine::Renderer::Render()
{
    // bind textures on corresponding texture units
    vbuffer->bind();
	ibuffer->bind();
    glActiveTexture(GL_TEXTURE0);
    texture->bind();
	render->fireRender(ibuffer->getIndexCount());
	texture->unbind();
	vbuffer->unBind();
	ibuffer->unBind();
};
