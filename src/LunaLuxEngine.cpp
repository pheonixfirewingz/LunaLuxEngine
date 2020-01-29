#include "LunaLuxEngine.h"

using namespace LunaLuxEngine;

void lunaLuxEngine::initEngine()
{
    if(debug_level_0) std::printf("%s\n", "loading LunaLuxEngine");
	window->setTitle(m_game_main->getGameName());
	window->createWindow();
	render->initRender();
	_is_paused_ = false;
    if(debug_level_0) std::printf("%s\n", "loading Game");
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