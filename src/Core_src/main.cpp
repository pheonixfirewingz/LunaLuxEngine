//
// Created by luket on 04/04/2020.
//
#include "LunaLuxEngineCore.h"
#include <Game.h>

int main()
{
    auto* eng = LLE;
    eng->runEngine(new PublicGame());
    free(eng);
}
