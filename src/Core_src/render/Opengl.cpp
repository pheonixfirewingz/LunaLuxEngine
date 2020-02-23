//
// Created by digitech on 19/02/2020.
//
#ifdef __linux__
#include <cstdio>
#include "Opengl.h"
using namespace LunaLuxEngine;

inline void WindowResizeCallback(int32 width, int32 height)
{
	glViewport(0, 0, width, height);
}

void OGLRenderer::initRender(window_api::CrossWindow* win)
{


	glc = glXCreateContext(CWin->getWindowL(), CWin->getWindowV(), NULL, GL_TRUE);
	glXMakeCurrent(CWin->getWindowL(), CWin->getWindowL_(), glc);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK) FOURCE_STOP("glew could not initialized engine boot failed")
}

void OGLRenderer::prepRender()
{
	CWin->setResizeCallback(&WindowResizeCallback);
	CWin->fireResizeCallback(CWin->getWindowW(), CWin->getWindowH());
}

void OGLRenderer::fireRender()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1., 1., -1., 1., 1., 20.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	glBegin(GL_QUADS);
	glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
	glColor3f(0., 1., 0.); glVertex3f(.75, -.75, 0.);
	glColor3f(0., 0., 1.); glVertex3f(.75, .75, 0.);
	glColor3f(1., 1., 0.); glVertex3f(-.75, .75, 0.);
	glEnd();
}

void OGLRenderer::postRender()
{
	glXSwapBuffers(CWin->getWindowL(), CWin->getWindowL_());
}

void OGLRenderer::destroyRender()
{
	glXMakeCurrent(CWin->getWindowL(), None, NULL);
	glXDestroyContext(CWin->getWindowL(), glc);
}
#endif // __linux__