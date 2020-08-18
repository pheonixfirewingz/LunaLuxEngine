//
// Created by luket on 23/01/2020.
//
#include <CrossWindow/WindowAPI.h>
#include "OpenGLRenderer.h"
#include "../Buffer.h"

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
	//----------this is part of the layout abstract to be removed when complete--------------------
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
	//---------------------------------------------------------------------------------------------------------
	glDrawElements(GL_TRIANGLES, indexcount, GL_UNSIGNED_INT, nullptr);
	//----------this is part of the layout abstract to be removed when complete--------------------
	glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
	//---------------------------------------------------------------------------------------------------------
	glBindVertexArray(0);
}
LunaLuxEngine::OGLRenderer::OGLRenderer()
{
    CWin.getNativeWindow()->setResizeCallback(&OGLWindowResizeCallback);
    gladLoadGL();
    printf("RENDERER API INFO VENDOR: %s VERSION: opengl %s GLSL_VERSION: glsl %s\n",
           glGetString(GL_VENDOR),glGetString(GL_VERSION),glGetString(GL_SHADING_LANGUAGE_VERSION));

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
}

LunaLuxEngine::OGLRenderer::~OGLRenderer()
{
    glDeleteVertexArrays(1, &VertexArrayID);
}


