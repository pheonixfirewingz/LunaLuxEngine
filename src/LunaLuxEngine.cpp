#include "LunaLuxEngine.h"

using namespace LunaLuxEngine;

void lunaLuxEngine::initEngine()
{
	std::printf("%s\n", "loading LunaLuxEngine");
	window->setTitle(m_game_main->getGameName());
	window->createWindow();
	render->initRender();
	_is_paused_ = false;
	std::printf("%s\n", "loading Game");
	if (m_game_main == nullptr)
		std::exit(-9);
	m_game_main->GameBoot();
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
	std::printf("%s\n\n", "Starting LunaLuxEngine Runloop");
	initEngine();
	while (!window->shouldClose())
	{
		updateEngine();
	}
	window->destoryWindow();
	std::printf("%s\n", "shutdown LunaLuxEngine");
}