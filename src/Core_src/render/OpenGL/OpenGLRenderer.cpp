//
// Created by luket on 23/01/2020.
//
#include "OpenGLRenderer.h"
#ifdef __linux__
#include <GL/glew.h>
#else
#include <glad/glad.h>
#endif

inline void OGLWindowResizeCallback(int32 width, int32 height)
{
	glViewport(0, 0, width, height);
}

void LunaLuxEngine::OGLRenderer::clearscreen(float colour[4])
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(colour[0], colour[1], colour[2], colour[3]);
}

GLuint VertexArrayID;
void LunaLuxEngine::OGLRenderer::initRender()
{
	CWin.getNativeWindow()->setResizeCallback(&OGLWindowResizeCallback);
#ifdef __linux__
	glewInit();
#else
    gladLoadGL();
#endif
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void LunaLuxEngine::OGLRenderer::fireRender(int indexcount)
{
	glBindVertexArray(VertexArrayID);
	//----------this is part of the layout abstract to be removed when complete--------------------
	glEnableVertexAttribArray(0);
	//---------------------------------------------------------------------------------------------------------
	glDrawElements(GL_TRIANGLES, indexcount, GL_UNSIGNED_INT, nullptr);
	//----------this is part of the layout abstract to be removed when complete--------------------
	glDisableVertexAttribArray(0);
	//---------------------------------------------------------------------------------------------------------
	glBindVertexArray(0);
}

void LunaLuxEngine::OGLRenderer::destroyRender()
{
	glDeleteVertexArrays(1, &VertexArrayID);
}