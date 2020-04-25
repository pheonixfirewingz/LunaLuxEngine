//
// Created by luket on 23/01/2020.
//
#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define CLION

#include<iostream>
using namespace std;

std::string get_current_dir()
{
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir( buff, FILENAME_MAX );
    string current_working_dir(buff);
    return "Working Directory: " + current_working_dir + "\n\n";
}

#include "Game.h"
#include <glad/glad.h>

static float vertex[] =
{
   -0.5f, -0.5f, 0.5f,
   -0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,

	/*-1.0f, -1.0f, 1.0f,
   -1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,*/
};

int indices[] =
{
	0, 1, 2,
	0, 2, 3,

	/*4, 5, 6,
	4, 6, 7*/
};

void PublicGame::preBoot()
{
    PublicGame::setGameName((int8*) "TestGame");
    printf(get_current_dir().c_str());
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
	//---------------------------------------------------------------------------------------------------------s
	vbuffer->unBind();
	char* data, * data1;
	std::string temp, temp1;
#ifdef CLION
        READFILE(temp, data, "../vertex.glsl");
        READFILE(temp1, data1, "../fragment.glsl");
#else
        READFILE(temp, data, "../../../vertex.glsl");
        READFILE(temp1, data1, "../../../fragment.glsl");
#endif
	shader->create();
	shader->compile(data, data1);
	shader->link();
}

void PublicGame::GameMain()
{
	PUSHTOENGINE(*vbuffer, *ibuffer, *shader);
}