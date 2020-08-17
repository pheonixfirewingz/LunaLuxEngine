#include "LunaLuxEngineCore.h"
#include <LLESDK/types.h>
#include <CrossWindow/WindowAPI.h>
#include "render/Renderer.h"
#include "common/EnginePanic.h"

namespace LunaLuxEngine
{
    bool opengl{false};
    void lunaLuxEngine::initEngine(bool &debug)
    {
        window_api::WindowInfo *info = new window_api::WindowInfo();
        //-----------------------------used to set apis-----------------------------------
#ifdef LLE_WINDOWS
        info->windowType = window_api::WindowType::Win32Window;
#elif defined(LLE_LINUX)
        info->windowType = window_api::WindowType::X11Window;
#else
#error "dose not currently support current platform"
#endif
        //----------------------------------------------------------------------------------
        CHECK_P(m_game_main, "no game class given")
        m_game_main->preBoot();
        info->title = m_game_main->getGameName();
        info->height = m_game_main->getWindowHeight();
        info->width = m_game_main->getWindowWidth();
        info->HaveWindowCreateOpenGLContext = opengl;
        CWin.giveWindowInfo(*info);
        CWin.createWindow();
        if(opengl) Renderer::get().initRender();
        m_game_main->GameBoot();
    }

    int8 lunaLuxEngine::updateEngine(bool &debug)
    {
        auto frameStart = std::chrono::high_resolution_clock::now();
        CWin.updateWindow();
        m_game_main->GameUpdate();
        if(!opengl) goto loop;
        Renderer::get().preRender();
        Renderer::get().beginLevel();
        m_game_main->GameLevel();
        Renderer::get().endLevel();
        Renderer::get().Render();
        loop:
        auto frameEnd = std::chrono::high_resolution_clock::now();
        m_frameTime = frameEnd - frameStart;
        return EXIT_SUCCESS;
    }

    void lunaLuxEngine::runEngine(Game *game, bool debug)
    {
        m_game_main = game;
        initEngine(debug);

        while (!CWin.shouldClose()) if (updateEngine(debug) != EXIT_SUCCESS)
            EnginePanic::get()->panic("Engine Could Not Complete Update");

        CWin.destoryWindow();
        free(m_game_main);
        m_game_main = nullptr;
    }
}