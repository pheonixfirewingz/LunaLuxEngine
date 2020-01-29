//
// Created by luket on 23/01/2020.
//

#ifndef LUNALUXENGINE_GAME_H
#define LUNALUXENGINE_GAME_H
#include <utils/IGame.h>

class TestGame : public Game
{
    void preBoot() override;
	void GameBoot() override;
	void GameMain() override;
};
#endif //LUNALUXENGINE_GAME_H
