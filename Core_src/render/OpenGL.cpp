//
// Created by luket on 16/01/2020.
//
#ifdef __linux__
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include "IRender.h"
#include "../window/Window.h"

void IRender::initRender()
{
    GLenum state  = glewInit();
    if (state != GLEW_OK) std::exit(-10);
}

void IRender::destroyRender()
{

}

void IRender::fireRender()
{
    for(int8 i = 0; i < entitys.size();i++)
    {
        /*glBindVertexArray(block.getMesh().getVao());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, block.getMesh().getIbo());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, block.getMesh().getMaterial().getTextureId());
        /*shader.bind();
        shader.setUniform("model", Matrix4f.transform(new Vector3f(0, 0, 0), block.getRotation(), block.getScale()));
        shader.setUniform("view", Matrix4f.view(camera.getPosition(), camera.getRotation()));
        shader.setUniform("projection", windowOld.getProjectionMatrix());
        shader.setUniform("positionOffset", block.getPosition());
        glDrawElementsInstanced(GL_TRIANGLES, block.getMesh().getIndices().length, GL_UNSIGNED_INT, 0, 1);
        //shader.unbind();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindVertexArray(0);*/
    }
}

void IRender::prepRender()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
#endif