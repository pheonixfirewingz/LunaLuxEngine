//
// Created by luket on 23/01/2020.
//
#include <cstdio>
#include "Game.h"
void TestGame::preBoot()
{
	TestGame::setGameName((int8*)"testGame");
	TestGame::setWindowSize(1280,720);
	TestGame::setNativeMode(true);
}

void TestGame::GameBoot()
{
	printf("loaded game");
}

void TestGame::GameMain()
{

}