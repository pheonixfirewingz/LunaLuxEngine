//
// Created by luket on 08/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include "API/WindowLib.h"

#include <memory>
#if __has_include(<xcb/xcb.h>)
#    include "linux/linuxWindows.hpp"
std::unique_ptr<LunaLux::LinuxWindow> window;
#endif
#if __has_include(<windows.h>)
#    include "Windows/WindowsWindow.hpp"
std::unique_ptr<LunaLux::WindowsWindow> window;
#endif
std::unique_ptr<LunaLux::IO> io = window->getIO();
int last_width, last_height;
std::string last;
namespace LunaLux
{
void windowCreate(const std::string & title, int width, int height) noexcept
{
    if (width != 0 || height != 0)
    {
#if __has_include(<windows.h>)
        window = std::make_unique<LunaLux::WindowsWindow>(title.c_str(), width, height);
#elif __has_include(<xcb/xcb.h>)
        window = std::make_unique<LunaLux::LinuxWindow>(title.c_str(), width, height);
#endif
        last_width = width;
        last_height = height;
        return;
    }
#if __has_include(<windows.h>)
    window = std::make_unique<LunaLux::WindowsWindow>(title.c_str(), width, height);
#elif __has_include(<xcb/xcb.h>)
    window = std::make_unique<LunaLux::LinuxWindow>(title.c_str(), 1280, 720);
#endif
    last_width = 1280;
    last_height = 720;
}

void *windowGetNative() noexcept
{
    return window->GetNativeWindow();
}

void windowChangeTitle(const std::string &title)
{
    if (title == last)
    {
        return;
    }
    last = title;
    window->ChangeWindowTitle(title.c_str());
}

bool shouldCloseWindow() noexcept
{
    return window->ShouldClose();
}

void windowUpdate() noexcept
{
    window->Update();
}

std::tuple<int, int> windowGetRectSize() noexcept
{
    return window->GetWindowSize();
}

void windowClose() noexcept
{
    window->Close();
}

bool isKeyDown(uint8_t keycode)
{
    return io->isButtonDown(keycode);
}

bool isMouseDown(uint8_t keycode)
{
    return io->isButtonDown(256 + keycode);
}

uint64_t getWheelDelta()
{
    return io->getWheelDelta();
}

std::tuple<int64_t, int64_t> getMousePosition()
{
    return io->getPosition();
}

bool hasWindowResized() noexcept
{
    int temp_width  = std::get<0>(windowGetRectSize()),
        temp_height = std::get<0>(windowGetRectSize());

    if (temp_width != last_width || temp_height != last_height)
    {
        last_width  = temp_width;
        last_height = temp_height;
        return true;
    }
    return false;
}

uint64_t getTime()
{
    return window->getTime();
}
}