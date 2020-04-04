//
// Created by luket on 23/01/2020.
//
#include <cstdio>
#include "Game.h"
#include <glad/glad.h>

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
	0, 2, 3
};

void TestGame::preBoot()
{
	TestGame::setGameName((int8*)"testGame");
	TestGame::setWindowSize(1280, 720);
	TestGame::setNativeMode(true);
}

void TestGame::GameBoot()
{
	vbuffer->create(vertex, sizeof(vertex));
	ibuffer->create(indices, sizeof(indices));
	vbuffer->bind();
	//----------this is part of the layout abstract to be removed when complete--------------------
	glBindAttribLocation(1, 0, "position");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//---------------------------------------------------------------------------------------------------------s
	vbuffer->unBind();
	char* data, * data1;
	std::string temp, temp1;
	READFILE(temp, data, "Debug/vertex.glsl");
	READFILE(temp1, data1, "Debug/fragment.glsl");
	shader->create();
	shader->compile(data, data1);
	shader->link();
	PUSHTOENGINE(vbuffer, ibuffer, shader);
}

void TestGame::GameMain()
{
}