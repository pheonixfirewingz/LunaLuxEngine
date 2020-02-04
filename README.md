# LunaLuxEngine V0.0.1
LunaLuxEngine is a 2D graphical engine.(Plan to add 3D after 2D)

----------------------------------------------------------------------------------------------
# Copyright ©Phoenixfirewingz 2019-2020

you may use our code in your projects but clear public credit must be given

Note: if someone contributes to the engine out side of Phoenixfirewingz© throught pull request their code will be under the MIT licence

#Contribution rules
----------------------------------------------------------------------------------------------
- keep formatting the same as the rest of the project
- if is a class you made or patched note it at the top of the class
- all notes (first party code changes to mutch to add notes before beta)

----------------------------------------------------------------------------------------------
# TODO
-------------When-Get-Mac--------------------
- create Window using cocoa for mac
- create Metal renderer and get a 2D_box on screen
# ------------------------

- create Vulkan context for linux and get a 2D_box on screen
- directX11 get a 2D_box on screen

Supported Platforms
-----------------------------------------------------------------------------------------------
- WINDOW(window finished. no renderer)
- LINUX (window not finished)

Planned Platforms
-----------------------------------------------------------------------------------------------
 - Windows
 - Linux (x11)(not Planning to Support wayland yet)
 - OSX

Planned Platforms (after decktop)
-----------------------------------------------------------------------------------------------
 - IOS
 - Android
 - Xbox

Working Progress
------------------------------------------------------------------------------------------------
- Cross platform window (will make this standalone in the future for public use)
- Vulkan Renderer (Linux X11 Only)
- Directx11 Renderer (window Desktop for now)

Current Known Bugs
------------------------------------------------------------------------------------------------
- Closing dose not work properly on linux x11
- DirectX 11 Shaders not being compiled

Minimum Start Code
------------------------------------------------------------------------------------------------
extend Game class in "#include <LLESDK/IGame.h>".
The pre boot is used to configure required variables in the game class.
- preBoot();
the game class is called by the engine as for the main game loop and inatalization faze this is done through
(engine logs will tell you if missing a config in the preBoot Stage)
- BootGame();
this is used to load external game fetures not part of the engine.
- GameMain();
this is used to allows custom game logic not handled by the engine to run in the engine's run loop

add to main class.
#include <LunaLuxEngineCore.h>

auto* eng = LLE;
eng->runEngine(new YourGameClass());
