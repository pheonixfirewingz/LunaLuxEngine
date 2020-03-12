//
// Created by luket on 23/01/2020.
//
#include "OpenGLRenderer.h"
#include <Windows.h>
using namespace LunaLuxEngine;

// This will identify our vertex buffer
GLuint vertexbuffer;
GLuint VertexArrayID;
inline void OGLWindowResizeCallback(int32 width, int32 height)
{
	glViewport(0, 0, width, height);
}

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};


void OGLRenderer::initRender()
{
	CWin.getNativeWindow()->setResizeCallback(&OGLWindowResizeCallback);
	gladLoadGL();
	//temp
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void OGLRenderer::fireRender()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

}

void OGLRenderer::destroyRender()
{
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteBuffers(1, &vertexbuffer);
}