#include "LunaLuxEngineCore.h"
#include <cstdio>
#include <thread>
#include "render/Buffer.h"
#include "utils/BufferUtil.h"
#include "render/Renderer.h"
namespace LunaLuxEngine
{
	VERTEX OurVertices[] =
	{
		VERTEX(VECTOR3(-0.5f, -0.5f, 0.5f), COLOUR(1.0f, 0.0f, 0.0f, 1.0f)),
		VERTEX(VECTOR3(-0.5f, 0.5f, 0.5f), COLOUR(0.0f, 1.0f, 0.0f, 1.0f)),
		VERTEX(VECTOR3(0.5f, 0.5f, 0.5f), COLOUR(0.0f, 0.0f, 1.0f, 1.0f)),
		VERTEX(VECTOR3(0.5f, -0.5f, 0.5f), COLOUR(0.0f, 1.0f, 0.0f, 1.0f))
	};

	int indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	void lunaLuxEngine::initEngine()
	{

		CHECK_P(m_game_main, "no game class given");
		m_game_main->preBoot();
		CHECK_P(m_game_main->getGameName(), "game name null");
		CHECK_N2(m_game_main->getWindowWidth(), "game Window Width not set");
		CHECK_N2(m_game_main->getWindowHeight(), "game Window Height not set");

		Renderer::get()->toggleDebug();
		CWin->setTitle(m_game_main->getGameName());
		CWin->setSize(m_game_main->getWindowWidth(), m_game_main->getWindowHeight());
		CWin->createWindow();
		Renderer::get()->initRender(CWin);
		BufferUtils::get()->createVBufAndAddToArray(OurVertices, 4);
		BufferUtils::get()->createIBufAndAddToArray(indices, 6);

	}
	int8 lunaLuxEngine::updateEngine()
	{
		CWin->updateWindow();
		m_game_main->GameMain();
		Renderer::get()->Render();
		return EXIT_SUCCESS;
	}

	void lunaLuxEngine::runEngine(Game* game)
	{
		m_game_main = game;
		initEngine();
		m_game_main->GameBoot();
		while (!CWin->shouldClose()) if (updateEngine() != EXIT_SUCCESS) exit(EXIT_FAILURE);
		CWin->destoryWindow();
		Renderer::get()->destroyRenderer();
		exit(EXIT_SUCCESS);
	}
}