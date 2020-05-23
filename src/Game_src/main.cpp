//
// Created by luket on 04/04/2020.
//
#include <LLESDK/Engine.h>
#include "Game.h"

int main()
{
    auto* eng = LLE;
    eng->runEngine(new PublicGame(),true,(char*)"-FallBackMode");
    free(eng);
}
