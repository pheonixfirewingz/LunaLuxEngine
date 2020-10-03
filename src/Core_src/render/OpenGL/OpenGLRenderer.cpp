//
// Created by luket on 23/01/2020.
//
#include <CrossWindow/WindowAPI.h>
#include "OpenGLRenderer.h"

inline void OGLWindowResizeCallback(int32 width, int32 height)
{
    glViewport(0, 0, width, height);
}

void LunaLuxEngine::OGLRenderer::clearscreen(float colour[4])
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(colour[0], colour[1], colour[2], colour[3]);
}

void LunaLuxEngine::OGLRenderer::fireRender(int indexcount)
{
    glBindVertexArray(VertexArrayID);
    glDrawElements(GL_TRIANGLES, indexcount, GL_UNSIGNED_INT, nullptr);
}

LunaLuxEngine::OGLRenderer::OGLRenderer()
{
    CWin.getNativeWindow()->setResizeCallback(&OGLWindowResizeCallback);
    gladLoadGL();
    printf("Engine and Game Log: RENDERER API VERSION: opengl %s\n", glGetString(GL_VERSION));
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
}

LunaLuxEngine::OGLRenderer::~OGLRenderer()
{
    glDeleteVertexArrays(1, &VertexArrayID);
}