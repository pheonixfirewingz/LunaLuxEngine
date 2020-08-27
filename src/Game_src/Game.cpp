//
// Created by luket on 23/01/2020.
//
#include <CrossWindow/WindowAPI.h>

using namespace LunaLuxEngine::window_api;
#include "Game.h"

void PublicGame::preBoot()
{
	PublicGame::setGameName((int8*)"TestGame");
	PublicGame::setWindowSize(1280, 720);
}

float vertices_[] =
        {
                // positions       // texture coords
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f    // top left
        };
unsigned int indices_[] =
        {
                0, 1, 2, 0, 2, 3
        };

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
