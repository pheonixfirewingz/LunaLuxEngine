//
// Created by luket on 20/01/2020.
//


#include <LunaLuxEngineCore.h>
#include "Game.h"
int main()
{
	auto* eng = LLE;
	eng->runEngine(new TestGame());
	free(eng);
}
