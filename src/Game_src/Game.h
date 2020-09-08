//
// Created by luket on 23/01/2020.
//
#ifndef LUNALUXENGINE_GAME_H
#define LUNALUXENGINE_GAME_H
#include <LLESDK/Engine.h>
#include <LLESDK/IGame.h>

class PublicGame : public Game
{
	void preBoot() override;
	void GameBoot() override;
	void GameUpdate() override;
	void GameLevel() override;
};
#endif //LUNALUXENGINE_GAME_H