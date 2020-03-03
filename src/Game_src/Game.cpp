//
// Created by luket on 23/01/2020.
//
#include <cstdio>
#include "Game.h"
#include <utils\BufferUtil.h>

VERTEX OurVertices[] =
{
	VERTEX(VECTOR3(-0.5f, -0.5f, 0.5f), COLOUR(1.0f, 0.0f, 0.0f, 1.0f)),
	VERTEX(VECTOR3(-0.5f, 0.5f, 0.5f), COLOUR(0.0f, 1.0f, 0.0f, 1.0f)),
	VERTEX(VECTOR3(0.5f, 0.5f, 0.5f), COLOUR(0.0f, 0.0f, 1.0f, 1.0f)),
	VERTEX(VECTOR3(0.5f, -0.5f, 0.5f), COLOUR(0.0f, 1.0f, 0.0f, 1.0f))
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
	LOG("loaded game");
}

void TestGame::GameMain()
{

}