//
// Created by luket on 23/01/2020.
//

#include<iostream>
using namespace std;

#include "Game.h"

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
}
void PublicGame::GameMain()
{
}