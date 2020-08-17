//
// Created by luket on 23/01/2020.
//
#include <CrossWindow/WindowAPI.h>

using namespace LunaLuxEngine::window_api;
#include "Game.h"

/*
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
};*/

void PublicGame::preBoot()
{
	PublicGame::setGameName((int8*)"TestGame");
	PublicGame::setWindowSize(1280, 720);
}

void PublicGame::GameBoot()
{

}
void PublicGame::GameUpdate()
{
    //temp for debug----
    if (CWin.getNativeWindow()->getInputController()->isKeyDown(LLE_KEY_1)) CWin.setShouldClose(true);
    //-----------------------
}

void PublicGame::GameLevel()
{

}
