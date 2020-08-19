//
// Created by luket on 19/08/2020.
//
#include "Renderer.h"
#include <CrossWindow/WindowAPI.h>
#include "OpenGL/OpenGLUtils.h"
#include "../fs/FileManager.h"


void LunaLuxEngine::Renderer::splash(std::string splash_image)
{
    VertexBuffer *splash_v_buffer = new VertexBuffer();
    IndexBuffer *splash_i_buffer = new IndexBuffer();
    Shader *splash_shader = new Shader();
    OpenGLTexture *splash_texture = new OpenGLTexture(FileManager::get()->getAbsolutePath(splash_image));
    float splash_vertices[] = {1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    unsigned int splash_indices[] = {0, 1, 2, 0, 2, 3};
    char *data = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec2 aTexCoord;\n\n"
                 "out vec2 TexCoord;\n\nvoid main()\n{\n\tgl_Position = vec4(aPos, 1.0);\n\tTexCoord = vec2(aTexCoord.x,"
                 "aTexCoord.y);\n}";
    char *data1 = "#version 330 core\nout vec4 FragColor;\n\nin vec2 TexCoord;\n\nuniform sampler2D texture1;\n\n"
                  "void main()\n{\n\tFragColor = texture(texture1, TexCoord);\n}";
    splash_v_buffer->create(splash_vertices, sizeof(splash_vertices));
    splash_i_buffer->create(splash_indices, sizeof(splash_indices));
    splash_v_buffer->bind();
    //----------this is part of the layout abstract to be removed when complete--------------------
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //---------------------------------------------------------------------------------------------------------
    splash_v_buffer->unBind();
    splash_shader->compile(data, data1);
    OpenGLUtils::setInt(splash_shader->getOGLSID(), "texture1", 0);
    splash_texture->bind();
    splash_v_buffer->bind();
    splash_i_buffer->bind();
    render->fireRender(splash_i_buffer->getIndexCount());
    splash_texture->unbind();
    splash_v_buffer->unBind();
    splash_i_buffer->unBind();
    CWin.updateWindow();
}