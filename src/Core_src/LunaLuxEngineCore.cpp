#include "LunaLuxEngineCore.h"
#include <CrossWindow/WindowAPI.h>
#include "render/Renderer.h"
#include "common/EnginePanic.h"
namespace LunaLuxEngine
{
	void lunaLuxEngine::initEngine(bool& debug)
	{
		if (debug) LOG("DEBUG: ACTIVE")
		else LOG("DEBUG: DE-ACTIVED")
			if (debug) LOG("Start Logging Engine")
				//-----------------------------used to set apis-----------------------------------
#ifdef __linux__
				CWin.setWindowType(window_api::WindowType::X11Window);
#elif WIN32
				CWin.setWindowType(window_api::WindowType::Win32Window);
#endif
		//----------------------------------------------------------------------------------
		CHECK_P(m_game_main, "no game class given")
			m_game_main->preBoot();
		CWin.setTitle(m_game_main->getGameName());
		CWin.setSize(m_game_main->getWindowWidth(), m_game_main->getWindowHeight());
		CWin.createWindow();
		if (debug)
		{
            LOG("created window")
			LOG("Finished Loading Engine")
			LOG("Loading Game")
		}
		m_game_main->GameBoot();
		if (debug) LOG("Finished Loading Game")
	}
	int8 lunaLuxEngine::updateEngine(bool& debug)
	{
		//temp for debug----
		if (CWin.getNativeWindow()->getInputController()->isKeyDown(window_api::LLE_KEY_C) && CWin.getNativeWindow()->getInputController()->isMouseButtonDown(window_api::LLE_BUTTON_MIDDLE)) CWin.setShouldClose(true);
		//-----------------------
		CWin.updateWindow();
		m_game_main->GameMain();
		Renderer::get().preRender();
		Renderer::get().Render();
		Renderer::get().postRender();
		return EXIT_SUCCESS;
	}

	void lunaLuxEngine::runEngine(Game* game, bool debug,char* data)
	{
		m_game_main = game;
		initEngine(debug);
		while (!CWin.shouldClose()) if (updateEngine(debug) != EXIT_SUCCESS) EnginePanic::get()->panic("Engine Could Not Complete Update");
		if (debug) LOG("Shutting Down Engine")
        CWin.destoryWindow();
		free(m_game_main);
        m_game_main = nullptr;
		if (debug) LOG("Stop Logging Engine")
	}
}