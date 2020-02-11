#include "LunaLuxEngineCore.h"
#include <cstdio>
namespace LunaLuxEngine
{
<<<<<<< HEAD
    CHECK_P(m_game_main , "no game class given")
    m_game_main->preBoot();
    CHECK_P(m_game_main->getGameName(),"game name null")
	CHECK_N2(m_game_main->getWindowWidth(),"game Window Width not set")
    CHECK_N2(m_game_main->getWindowHeight(),"game Window Height not set")

#ifdef WIN32
	if (m_game_main->getShouldUsNativeRenderer()) render = new DXRenderer();
	else
#endif
    //render = new VKRenderer();
	//render->toggleDebug();
	CWin->setTitle(m_game_main->getGameName());
	CWin->setSize(m_game_main->getWindowWidth(),m_game_main->getWindowHeight());
	CWin->createWindow();
	//render->initRender(CWin);
	Core_Physics_Controller->initPhysicsEngine();
}

int8 lunaLuxEngine::updateEngine()
{
	//render->prepRender();
	CWin->updateWindow();
	Core_Physics_Controller->updatePhysicsEngine();
	m_game_main->GameMain();
	//render->fireRender();
	//render->postRender();
	return EXIT_SUCCESS;
}

void lunaLuxEngine::runEngine(Game* game)
{
	m_game_main = game;
    initEngine();
	m_game_main->GameBoot();
	while (!CWin->shouldClose())
	{
		CHECK_N(updateEngine(),"engine failed to update")
		//printf("%s%d%s%d\n","X:",Input::Input::get()->getPosX()," Y: ",Input::Input::get()->getPosY());
	}
	//render->destroyRender();
	CWin->destoryWindow();
	exit(0);
=======
	void lunaLuxEngine::initEngine()
	{
		if (m_game_main == nullptr)
		{
			printf("no game class given");
			exit(EXIT_FAILURE);
		}
		m_game_main->preBoot();

		if (m_game_main->getGameName() == nullptr)
		{
			printf("game name null");
			exit(EXIT_FAILURE);
		}
		if (m_game_main->getWindowWidth() == 0)
		{
			printf("game Window Width not set");
			exit(EXIT_FAILURE);
		}
		if (m_game_main->getWindowHeight() == 0)
		{
			printf("game Window Height not set");
			exit(EXIT_FAILURE);
		}
		if (m_game_main->getShouldUsNativeRenderer()) render = new DXRenderer();
		else render = new VKRenderer();
		render->toggleDebug();
		CWin->setTitle(m_game_main->getGameName());
		CWin->setSize(m_game_main->getWindowWidth(), m_game_main->getWindowHeight());
		CWin->createWindow();
		render->initRender(CWin);
		//Core_Physics_Controller->initPhysicsEngine();
	}

	int8 lunaLuxEngine::updateEngine()
	{
		render->prepRender();
		CWin->updateWindow();
		//Core_Physics_Controller->updatePhysicsEngine();
		m_game_main->GameMain();
		render->fireRender();
		return EXIT_SUCCESS;
	}

	void lunaLuxEngine::runEngine(Game* game)
	{
		m_game_main = game;
		initEngine();
		m_game_main->GameBoot();
		while (!CWin->shouldClose())
		{
			if (updateEngine() != EXIT_SUCCESS) exit(EXIT_FAILURE);
		}
		render->destroyRender();
		CWin->destoryWindow();
		exit(0);
	}
>>>>>>> master
}