#include "LunaLuxEngineCore.h"
#include <CrossWindow/WindowAPI.h>
#include "render/Renderer.h"
#include "common/EnginePanic.h"

namespace LunaLuxEngine
{
    bool opengl{true};

    void lunaLuxEngine::initEngine(bool &debug)
    {
        auto *info = new window_api::WindowInfo();
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
        CWin.initWindow(*info);
        Renderer::get();
        m_game_main->GameBoot();
    }

    int8 lunaLuxEngine::updateEngine(bool &debug)
    {
        CWin.updateWindow();
        m_game_main->GameUpdate();
        if (!opengl)
        { goto loop; }
        Renderer::get().preRender();
        m_game_main->GameLevel();
        Renderer::get().Render();
        loop:

        return EXIT_SUCCESS;
    }

    void lunaLuxEngine::runEngine(Game *game, bool debug)
    {
        m_game_main = game;
        initEngine(debug);
        while (!CWin.shouldClose())
        {
            if (updateEngine(debug) != EXIT_SUCCESS)
            {
                EnginePanic::get()->panic("Engine Failed Update");
            }
        }
        CWin.destoryWindow();
        free(m_game_main);
    }
}