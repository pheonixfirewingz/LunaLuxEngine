//
// Created by luket on 04/04/2020.
//
#include <LLESDK/Engine.h>
#include "Game.h"
int main()
{
    LunaLuxEngine::lunaLuxEngine::get()->runEngine(new PublicGame(),true);
}
