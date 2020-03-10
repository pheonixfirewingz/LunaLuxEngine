#include "LunaLuxEngineCore.h"
#include "render/Renderer.h"
namespace LunaLuxEngine
{
	void lunaLuxEngine::initEngine()
	{
		CHECK_P(m_game_main, "no game class given");
		m_game_main->preBoot();
		CHECK_P(m_game_main->getGameName(), "game name null");
		CHECK_N2(m_game_main->getWindowWidth(), "game Window Width not set");
		CHECK_N2(m_game_main->getWindowHeight(), "game Window Height not set");
		CWin.setTitle(m_game_main->getGameName());
		CWin.setSize(m_game_main->getWindowWidth(), m_game_main->getWindowHeight());
		CWin.createWindow();
		Renderer::get()->preInitRenderer(DIRECT_X_ELEVEN);
		Renderer::get()->initRender();
	}
	int8 lunaLuxEngine::updateEngine()
	{
		//temp for debug----
		if (CWin.isKeyDown(LLE_KEY_C) && CWin.isMouseButtonDown(LLE_BUTTON_MIDDLE)) CWin.setShouldClose(true);
		//-----------------------
		CWin.updateWindow();
		m_game_main->GameMain();
		Renderer::get()->preRender();
		Renderer::get()->Render();
		Renderer::get()->postRender();
		return EXIT_SUCCESS;
	}

	void lunaLuxEngine::runEngine(Game* game)
	{
		m_game_main = game;
		initEngine();
		m_game_main->GameBoot();
		while (!CWin.shouldClose()) if (updateEngine() != EXIT_SUCCESS) exit(EXIT_FAILURE);
		Renderer::get()->Release();
		free(m_game_main);
	}
}