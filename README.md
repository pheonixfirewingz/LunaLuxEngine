![img](https://www.code-inspector.com/project/4310/status/svg)  ![img](https://www.code-inspector.com/project/4310/score/svg)
# LunaLuxEngine V0.0.2
LunaLuxEngine is a 2D graphical engine.(Plan to add 3D after 2D)

----------------------------------------------------------------------------------------------

## Contribution rules

- keep formatting the same as the rest of the project
- focuse on speed and optamization
- if is a class you made or patched note it at the top of the class
- try to be memory safe (not required if works)

## Formatting

- cammel Case for names of functions
- all lower case for private varables
- all upper case for Public varables
- used the Visual Studios default code format for brackets and indents
- if and else statements with 1 funtion or opperation in them don't need brakets
- naming convention must be understandable with out notes
- if code is final and will not be changes detailed notes must be added
- if code will be changed basic notes must be added for other devs to understand

## TODO
- Create Window using cocoa for mac (waiting for OSX availability)
- Create Metal renderer and get a 2D_box on screen (waiting for OSX availability)
- Create Vulkan context for linux and get a 2D_box on screen
- DirectX11 get a character on screen

## WIP
- Windows DirectX 11 renderer
- Linux OpenGL Renderer
- Linux Window Support

-----------------------
## Platforms

### Supported Platforms
- WINDOW (window adding as needed. working on DX11 renderer)

### Planned Platforms (Stage 1)
-----------------------------------------------------------------------------------------------
 - Windows 10
 - Linux ubuntu 18.04 STL (x11 window Manager)(no for Support wayland Window Manager)
 - OSX high mountain

### Planned Platforms (Stage 2)
-----------------------------------------------------------------------------------------------
 - IOS 13 and up
 - Android api 20 and up
 - Switch (versions unknown)

### Planned Platforms (Stage 3)
-----------------------------------------------------------------------------------------------
 - Xbox One and up
 - PlayStation 4 and up

## Known issues

## Code Quality Issues
-----------------------------------------------------------------------------------------------
- Violation = Important/security (CWE-120, CWE-20)
- Problem = Check buffer boundaries if used in a loop including recursive loops 
- File = Reader.h
- Line = 23
-----------------------------------------------------------------------------------------------
- Violation = Minor/best practice
- Problem = The class 'BufferUtils' does not have a constructor although it has private member variables.
- File = Buffer.h
- Line = 11

## Getting started

### Minimum Start Code
-----------------------
Extend Game class in "#include <LLESDK/IGame.h>".
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

-----------------------

# The legal stuff

## LICENCE
Copyright 2020 Luke Shore

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, not including limitations to the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

- You, the user, use this software without royalties if you have made yourself known to the project, plan to contribute and the developer, Luke Shore, has agreed.

- You, the user, understand that you *must* provide clear evidence that you have utilised our project in your non/commercial project.

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
