#include "LunaLuxEngineCore.h"
#include <cstdio>
#include <thread>
#include "render/Buffer.h"
#include "utils/BufferUtil.h"
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

		CHECK_P(m_game_main, "no game class given")
			m_game_main->preBoot();
		CHECK_P(m_game_main->getGameName(), "game name null")
			CHECK_N2(m_game_main->getWindowWidth(), "game Window Width not set")
			CHECK_N2(m_game_main->getWindowHeight(), "game Window Height not set")

#ifdef WIN32
			if (m_game_main->getShouldUsNativeRenderer()) render = new DXRenderer();
#endif
#ifdef __linux__
		render = new OGLRenderer();
#endif
		render->toggleDebug();
		CWin->setTitle(m_game_main->getGameName());
		CWin->setSize(m_game_main->getWindowWidth(), m_game_main->getWindowHeight());
		CWin->createWindow();
		render->initRender(CWin);
		BufferUtils::get()->createVBufAndAddToArray(OurVertices, 4);
		BufferUtils::get()->createIBufAndAddToArray(indices, 6);
	}
	int8 lunaLuxEngine::updateEngine()
	{
		CWin->updateWindow();
		m_game_main->GameMain();
		render->prepRender();
		render->fireRender();
		render->postRender();
		return EXIT_SUCCESS;
	}

	void lunaLuxEngine::runEngine(Game* game)
	{
		m_game_main = game;
		initEngine();
		m_game_main->GameBoot();
		while (!CWin->shouldClose()) if (updateEngine() != EXIT_SUCCESS) exit(EXIT_FAILURE);
		render->destroyRender();
		CWin->destoryWindow();
		exit(EXIT_SUCCESS);
	}
}