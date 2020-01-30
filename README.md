# LunaLuxEngine V0.0.1
LunaLuxEngine is a 2D and 3D graphical engine.

----------------------------------------------------------------------------------------------
# Copyright © Echo Studios 2019-2020

you may use our code in your projects but clear public credit must be given
----------------------------------------------------------------------------------------------
# TODO
- remove dependence on glfw on mac

Supported Platforms
-----------------------------------------------------------------------------------------------
 - Windows

Planned Platforms
-----------------------------------------------------------------------------------------------
 - Linux
 - OSX
 - SerenityOS (maybe)

Planned Platforms (after decktop)
-----------------------------------------------------------------------------------------------
 - IOS
 - Android
 - Xbox

Working Progress
------------------------------------------------------------------------------------------------
- Cross platform window (will make this standalone in the future for public use)
- Opengl Renderer (Linux Only)
- Directx11 Renderer (window Desktop for now)

Current Bugs
------------------------------------------------------------------------------------------------
- Window is crashing on windows (win32) need rewrite

Minimum Start Code
------------------------------------------------------------------------------------------------
extend Game class.
The pre boot is used to configure required variables in the game class.
- preBoot();
the game class is called by the engine as for the main game loop and inatalization faze this is done through
- BootGame();
this is used to load external game fetures not part of the engine.
- GameMain();
this is used to allows custom game logic not handled by the engine to run in the engine's run loop

add to main class.
#include <LunaLuxEngineCore.h>

auto* eng = LunaLuxEngine::lunaLuxEngine::get();

eng->m_game_main = new YourGameClass();

eng->runEngine();
