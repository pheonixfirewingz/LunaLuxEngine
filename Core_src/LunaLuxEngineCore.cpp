#include "LunaLuxEngineCore.h"
#include <cstdio>
using namespace LunaLuxEngine;

void lunaLuxEngine::initEngine()
{
    if(debug_level_0) std::printf("%s\n", "loading LunaLuxEngine");
    if (m_game_main == nullptr)
    {
        std::printf("no game class given");
        std::exit(-1);
    }
    m_game_main->preBoot();

    if(m_game_main->getGameName() == nullptr)
    {
        std::printf("game name null");
        std::exit(-1);
    }
	if(m_game_main->getWindowWidth() == 0)
	{
		std::printf("game Window Width not set");
		std::exit(-1);
	}
	if(m_game_main->getWindowHeight() == 0)
	{
		std::printf("game Window Height not set");
		std::exit(-1);
	}
	window->setTitle(m_game_main->getGameName());
	window->setSize(m_game_main->getWindowWidth(),m_game_main->getWindowHeight());
	window->createWindow();
#ifdef WIN32
	render->initRender(window->getWindow());
#else
	render->initRender();
	Core_Physics_Controller->initPhysicsEngine();
#endif
	_is_paused_ = false;
	if (m_game_main == nullptr)
		std::exit(-9);
}

int8 lunaLuxEngine::updateEngine()
{
	if (_is_paused_) render->prepRender();
	window->updateWindow();
	if (_is_paused_)
	{
		m_game_main->GameMain();
		render->fireRender();
	}
	return 0;
}

bool lunaLuxEngine::isGamePaused()
{
	return _is_paused_; 
}
void lunaLuxEngine::set3D()
{
	_2DOr3D_ = true;
}

void lunaLuxEngine::runEngine(Game* game)
{
	m_game_main = game;
    initEngine();
	std::printf("%s\n", "loaded LunaLuxEngine");
	m_game_main->GameBoot();
    if(debug_level_0) std::printf("%s\n\n", "Starting LunaLuxEngine Runloop");
	while (!window->shouldClose())
	{
		updateEngine();
	}
    std::printf("\n%s", "shutdown LunaLuxEngine");
	window->destoryWindow();
	std::exit(0);
}