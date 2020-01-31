# LunaLuxEngine V0.0.1
LunaLuxEngine is a 2D and 3D graphical engine.

----------------------------------------------------------------------------------------------
# Copyright Â© Echo Studios 2019-2020

you may use our code in your projects but clear public credit must be given

Note: if someone contributes to the engine out side of Echo-Studios© throught pull request there code will be under the MIT licence

#Contribution rules
----------------------------------------------------------------------------------------------
- keep formatting the same as the rest of the project
- if is a class you made or patched note it at the top of the class
- all notes (first party code changes to mutch to add notes before beta)

----------------------------------------------------------------------------------------------
# TODO
- remove dependence on glfw on mac

Supported Platforms
-----------------------------------------------------------------------------------------------
- NULL
Planned Platforms
-----------------------------------------------------------------------------------------------
 - Windows
 - Linux
 - OSX

Planned Platforms (after decktop)
-----------------------------------------------------------------------------------------------
 - IOS
 - Android
 - Xbox

Working Progress
------------------------------------------------------------------------------------------------
- Cross platform window (will make this standalone in the future for public use)
- Vulkan Renderer (Linux Only)
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
