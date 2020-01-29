//
// Created by luket on 20/01/2020.
//
#include <LunaLuxEngineCore.h>
#include "Game.h"
int main()
{
	auto* eng = LunaLuxEngine::lunaLuxEngine::get();
	eng->m_game_main = new TestGame();
	eng->runEngine();
	return 0;
}

