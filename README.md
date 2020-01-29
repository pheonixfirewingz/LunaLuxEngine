# LunaLuxEngine V0.0.1
LunaLuxEngine is a 2D and 3D graphical engine.

----------------------------------------------------------------------------------------------
# Copyright © Echo Studios 2019-2020

you may use our code in your projects but clear public credit must be given
----------------------------------------------------------------------------------------------
# TODO
- remove dependence on glfw on linux & mac

Supported Platforms
-----------------------------------------------------------------------------------------------
 - Windows

Planned Platforms
-----------------------------------------------------------------------------------------------
 - Linux
 - OSX
 - SerenityOS

Planned Platforms (after decktop)
-----------------------------------------------------------------------------------------------
 - IOS
 - Android
 - Xbox

Works in Progress
------------------------------------------------------------------------------------------------
- Cross platform window (will make this standalone in the future for public used)
- Opengl Renderer (Linux Only)
- Directx11 Renderer (window Desktop for now)

Minimum Start Code
------------------------------------------------------------------------------------------------
extend Game class.

the game class is called by the engine as for the main game loop and inatalization faze this is done through
- BootGame();
this is used to load external game fetures not part of the engine.
- GameMain();
this is used to allows custom game logic not handled by the engine to run in the engine's run loop

add to main class.

auto* eng = LunaLuxEngine::lunaLuxEngine::get();

eng->m_game_main = new YourGameClass();

eng->runEngine();
