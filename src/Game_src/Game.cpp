//
// Created by luket on 23/01/2020.
//

#include<iostream>
using namespace std;

#include "Game.h"
#ifdef __linux__
#include <GL/glew.h>
#else
#include <glad/glad.h>
#endif

static float vertex[] =
{
   -0.5f, -0.5f, 0.5f,
   -0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
};

static float vertex2[] =
{
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
};

int indices[] =
{
	0, 1, 2,
	0, 2, 3,
};

int indices2[] =
{
	0, 1, 2,
	0, 2, 3,
};

void PublicGame::preBoot()
{
	PublicGame::setGameName((int8*)"TestGame");
	PublicGame::setWindowSize(1280, 720);
	PublicGame::setNativeMode(true);
}

void PublicGame::GameBoot()
{
	vbuffer->create(vertex, sizeof(vertex));
	ibuffer->create(indices, sizeof(indices));
	vbuffer->bind();
	//----------this is part of the layout abstract to be removed when complete--------------------
	glBindAttribLocation(1, 0, "position");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//---------------------------------------------------------------------------------------------------------
	vbuffer->unBind();
	ibuffer->unBind();

	vbufferx->create(vertex2, sizeof(vertex2));
	ibufferx->create(indices2, sizeof(indices2));
	vbufferx->bind();
	//----------this is part of the layout abstract to be removed when complete--------------------
	glBindAttribLocation(1, 0, "position");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//---------------------------------------------------------------------------------------------------------
	vbufferx->unBind();
	ibuffer->unBind();

	shader->create();
	shader->compile("#version 330 core \n layout(location = 0) in vec3 position; \n out vec4 vertexColor; \n float shift_factor = 0.0; \n void main() \n { \n gl_Position = vec4(position, 1.0);\n vertexColor = vec4(position.x + shift_factor, position.y + shift_factor, 0.0, 1.0); \n };", "#version 330 core \n out vec4 FragColor; \n in vec4 vertexColor; \n void main() \n { \n FragColor = vertexColor; \n	};");
	shader->link();
	LunaLuxEngine::Renderer::get().pushDataToRenderer(*vbuffer, *ibuffer, *shader);
}
void PublicGame::GameMain()
{
	// to fix buffer swaping 
	if (CWin.getNativeWindow()->getInputController()->isKeyDown(LunaLuxEngine::window_api::LLE_KEY_1))
	{
		LunaLuxEngine::Renderer::get().pushDataToRenderer(*vbuffer, *ibuffer, *shader);
	}
	if (CWin.getNativeWindow()->getInputController()->isKeyDown(LunaLuxEngine::window_api::LLE_KEY_2))
	{
		LunaLuxEngine::Renderer::get().pushDataToRenderer(*vbufferx, *ibufferx, *shader);
	}
}