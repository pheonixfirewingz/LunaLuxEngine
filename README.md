# LunaLuxEngine V0.0.2
LunaLuxEngine is a 2D graphical engine.(Plan to add 3D after 2D)

----------------------------------------------------------------------------------------------
# LICENCE
Copyright 2020 Phoenixfirewingz

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

you can only used this software free if you are a Known Group or Game Studio To contribute to the Engine's Development.
if you are not a Known Group or Game Studio To contribute to the Engine's Development then you must give Clean undesputed Evidence that you used this software.

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# Contribution rules

- keep formatting the same as the rest of the project
- focuse on speed and optamization
- if is a class you made or patched note it at the top of the class

# Formatting

- cammel Case for names of functions
- all lower case for private varables
- all upper case for Public varables
- used the Visual Studios default code format for brackets and indents
- if and else statements with 1 funtion or opperation in them don't need brakets
- naming convention must be understandable with out notes
- if code is final and will not be changes detailed notes must be added
- if code will be changed basic notes must be added for other devs to understand

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
 - Windows 10
 - Linux ubuntu 18.04 STL (x11 window Manager)(no for Support wayland Window Manager)
 - OSX high mountain

Planned Platforms (after decktop)
-----------------------------------------------------------------------------------------------
 - IOS 13 and up
 - Android api 20 and up
 - Xbox One and up
 - PlayStation 4 and up
 - Switch (versions unknown)

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
