#include "LunaLuxEngineCore.h"

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
	window->setTitle(m_game_main->getGameName());
	window->createWindow();
	render->initRender();
	Core_Physics_Controller->initPhysicsEngine();
	_is_paused_ = false;
    if(debug_level_0) std::printf("%s\n", "loading Game");
<<<<<<< HEAD:Core_src/LunaLuxEngineCore.cpp
	m_game_main->GameBoot();
=======
	if (m_game_main == nullptr)
		std::exit(-9);
>>>>>>> master:src/LunaLuxEngine.cpp
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

void lunaLuxEngine::runEngine()
{
    initEngine();
	std::printf("\n%s\n", "loaded LunaLuxEngine");
	m_game_main->GameBoot();
    if(debug_level_0) std::printf("%s\n\n", "Starting LunaLuxEngine Runloop");
	while (!window->shouldClose())
	{
		updateEngine();
	}
    std::printf("%s\n", "shutdown LunaLuxEngine");
	window->destoryWindow();

}