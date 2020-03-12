#include "LunaLuxEngineCore.h"
#include "render/RenderEngine.h"
#include "window/WindowAPI.h"
namespace LunaLuxEngine
{
	void lunaLuxEngine::initEngine()
	{
		//-----------------------------used to set apis-----------------------------------
		CWin.setWindowType(window_api::WindowType::Win32Window);
		Renderer::get()->preInitRenderer(0);
		//----------------------------------------------------------------------------------
		CHECK_P(m_game_main, "no game class given");
		m_game_main->preBoot();
		CHECK_P(m_game_main->getGameName(), "game name null");
		CHECK_N2(m_game_main->getWindowWidth(), "game Window Width not set");
		CHECK_N2(m_game_main->getWindowHeight(), "game Window Height not set");
		CWin.setTitle(m_game_main->getGameName());
		CWin.setSize(m_game_main->getWindowWidth(), m_game_main->getWindowHeight());
		CWin.createWindow();
		Renderer::get()->initRender();
	}
	int8 lunaLuxEngine::updateEngine()
	{
		//temp for debug----
		if (CWin.getNativeWindow()->getInputController()->isKeyDown(window_api::LLE_KEY_C) && CWin.getNativeWindow()->getInputController()->isMouseButtonDown(window_api::LLE_BUTTON_MIDDLE)) CWin.setShouldClose(true);
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