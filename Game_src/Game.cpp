//
// Created by luket on 23/01/2020.
//
#include "Game.h"
#include <cstdio>

void TestGame::preBoot()
{
	TestGame::setGameName((char*)"testGame");
	TestGame::setWindowSize(1280,720);
}

void TestGame::GameBoot()
{
	std::printf("loaded game");
}

void TestGame::GameMain()
{

}