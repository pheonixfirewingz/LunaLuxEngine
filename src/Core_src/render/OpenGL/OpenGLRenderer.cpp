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

void OGLRenderer::initRender()
{
	CWin.setResizeCallback(&OGLWindowResizeCallback);
	Renderer::get()->instance.createOGLGPUInstance();
	gladLoadGL();
	//temp
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void OGLRenderer::fireRender()
{

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
	SwapBuffers(Renderer::get()->instance.getGPUDevice()->dc);
}

void OGLRenderer::destroyRender()
{
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteBuffers(1, &vertexbuffer);
}