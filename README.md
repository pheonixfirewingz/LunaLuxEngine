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

Works in Progress
------------------------------------------------------------------------------------------------
-Cross platform window

Minimum Start Code
------------------------------------------------------------------------------------------------
extend Game class.

add 	to main.

auto* eng = LunaLuxEngine::lunaLuxEngine::get();

eng->m_game_main = new YourGameClass();

eng->runEngine();
