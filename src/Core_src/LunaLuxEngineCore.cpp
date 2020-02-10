#include "LunaLuxEngineCore.h"
#include <cstdio>
using namespace LunaLuxEngine;

void lunaLuxEngine::initEngine()
{
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
}