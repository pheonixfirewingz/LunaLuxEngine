//
// Created by luket on 23/01/2020.
//
#ifndef LUNALUXENGINE_GAME_H
#define LUNALUXENGINE_GAME_H
#include <LLESDK/IGame.h>
#include <LLESDK/Engine.h>

class TestGame : public Game
{
	LunaLuxEngine::VertexBuffer* vbuffer = new LunaLuxEngine::VertexBuffer();
	LunaLuxEngine::IndexBuffer* ibuffer = new LunaLuxEngine::IndexBuffer();
	LunaLuxEngine::Shader* shader = new LunaLuxEngine::Shader();
	void preBoot() override;
	void GameBoot() override;
	void GameMain() override;
};
#endif //LUNALUXENGINE_GAME_H
