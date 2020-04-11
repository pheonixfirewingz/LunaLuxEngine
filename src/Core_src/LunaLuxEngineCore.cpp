#include "LunaLuxEngineCore.h"
#include "render/RenderEngine.h"
#include "window/WindowAPI.h"
#include "common/EnginePanic.h"
namespace LunaLuxEngine
{
	void lunaLuxEngine::initEngine()
	{
		LOG("Start Logging Engine");
		//-----------------------------used to set apis-----------------------------------
		CWin.setWindowType(window_api::WindowType::Win32Window);
		Renderer::get().preInitRenderer(currentAPItype);
		//----------------------------------------------------------------------------------
		CHECK_P(m_game_main, "no game class given");
		m_game_main->preBoot();
		CWin.setTitle(m_game_main->getGameName());
		CWin.setSize(m_game_main->getWindowWidth(), m_game_main->getWindowHeight());
		CWin.createWindow();
		LOG("created window");
		Renderer::get().initRender();
		LOG("Initalized Renderer");
		LOG("Finished Loading Engine");
		LOG("Loading Game");
		m_game_main->GameBoot();
		LOG("Finished Loading Game");
	}
	int8 lunaLuxEngine::updateEngine()
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

	void lunaLuxEngine::runEngine(Game* game)
	{
		m_game_main = game;
		initEngine();
		while (!CWin.shouldClose()) if (updateEngine() != EXIT_SUCCESS) EnginePanic::get()->panic("Engine Could Not Complete Update");
		LOG("Shutting Down Engine");
		Renderer::get().Release();
		free(m_game_main);
		LOG("Stop Logging Engine");
	}
}