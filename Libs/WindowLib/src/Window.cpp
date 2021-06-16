//
// Created by luket on 08/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include "API/WindowLib.h"
<<<<<<< HEAD:src/Window.cpp
#include "Platform.h"
#include "IO.hpp"
//This code is self explanatory so no documentation required
#ifdef LLE_WINDOWS
#include "Windows/WindowsWindow.hpp"
#endif
#ifdef LLE_LINUX
#include "linux/linuxWindows.hpp"
#endif
int last_width,last_height;
std::string last_title_change_to;
void LunaLux::createWindow(const std::string& title, int width, int height)
=======

#include <memory>
#if __has_include(<windows.h>)
#    include "Windows/WindowsWindow.hpp"
std::unique_ptr<LunaLux::WindowsWindow> window;
#endif
std::unique_ptr<LunaLux::IO> io = window->getIO();
int last_width, last_height;
std::string last;
namespace LunaLux
>>>>>>> Dev:Src/WindowLib.cpp
{
void windowCreate(const std::string & title, int width, int height) noexcept
{
    if (width != 0 || height != 0)
    {
<<<<<<< HEAD:src/Window.cpp
#ifdef LLE_WINDOWS
        WindowsWindow::Get()->Open(const_cast<char *>(title.c_str()), width, height);
#endif
#ifdef LLE_LINUX
        LinuxWindow::get()->Open(const_cast<char *>(title.c_str()), width, height);
#endif
=======
        window = std::make_unique<LunaLux::WindowsWindow>(title.c_str(), width, height);
>>>>>>> Dev:Src/WindowLib.cpp
        last_width = width;
        last_height = height;
        return;
    }
<<<<<<< HEAD:src/Window.cpp
#ifdef LLE_WINDOWS
    WindowsWindow::Get()->Open(const_cast<char *>(title.c_str()), 1280,720);
#endif
#ifdef LLE_LINUX
    LinuxWindow::get()->Open(const_cast<char *>(title.c_str()), 1280, 720);
#endif
=======
    window = std::make_unique<LunaLux::WindowsWindow>(title.c_str(), 1280, 720);
>>>>>>> Dev:Src/WindowLib.cpp
    last_width = 1280;
    last_height = 720;
}

void *windowGetNative() noexcept
{
<<<<<<< HEAD:src/Window.cpp
#ifdef LLE_WINDOWS
    return (void*) WindowsWindow::Get()->GetNativeWindow();
#endif
#ifdef LLE_LINUX
    return LinuxWindow::get()->GetNativeWindow();
#endif
=======
    return window->GetNativeWindow();
>>>>>>> Dev:Src/WindowLib.cpp
}

void windowChangeTitle(const std::string &title)
{
<<<<<<< HEAD:src/Window.cpp
    if(title == last_title_change_to) return;
    last_title_change_to = title;
#ifdef LLE_WINDOWS
    WindowsWindow::Get()->ChangeWindowTitle(const_cast<char *>(title.c_str()));
#endif
#ifdef LLE_LINUX
    LinuxWindow::get()->ChangeWindowTitle(const_cast<char *>(title.c_str()));
#endif
=======
    if (title == last)
    {
        return;
    }
    last = title;
    window->ChangeWindowTitle(title.c_str());
>>>>>>> Dev:Src/WindowLib.cpp
}

bool shouldCloseWindow() noexcept
{
<<<<<<< HEAD:src/Window.cpp
#ifdef LLE_WINDOWS
    WindowsWindow::Get()->LimitFrameRate(fps);
#endif
#ifdef LLE_LINUX
    LinuxWindow::get()->LimitFrameRate(fps);
#endif
=======
    return window->ShouldClose();
>>>>>>> Dev:Src/WindowLib.cpp
}

void windowUpdate() noexcept
{
<<<<<<< HEAD:src/Window.cpp
#ifdef LLE_WINDOWS
    return WindowsWindow::ShouldClose();
#endif
#ifdef LLE_LINUX
    return LinuxWindow::get()->ShouldClose();
#endif
=======
    window->Update();
>>>>>>> Dev:Src/WindowLib.cpp
}

std::tuple<int, int> windowGetRectSize() noexcept
{
<<<<<<< HEAD:src/Window.cpp
#ifdef LLE_WINDOWS
    return WindowsWindow::GetWindowSize();
#endif
#ifdef LLE_LINUX
    return LinuxWindow::get()->GetWindowSize();
#endif
=======
    return window->GetWindowSize();
>>>>>>> Dev:Src/WindowLib.cpp
}

void windowClose() noexcept
{
<<<<<<< HEAD:src/Window.cpp
#ifdef LLE_WINDOWS
    WindowsWindow::Get()->Update();
#endif
#ifdef LLE_LINUX
    LinuxWindow::get()->Update();
#endif
=======
    window->Close();
>>>>>>> Dev:Src/WindowLib.cpp
}

bool isKeyDown(uint8_t keycode)
{
<<<<<<< HEAD:src/Window.cpp
#ifdef LLE_WINDOWS
    WindowsWindow::Get()->Close();
#endif
#ifdef LLE_LINUX
    LinuxWindow::get()->Close();
#endif
=======
    return io->isButtonDown(keycode);
>>>>>>> Dev:Src/WindowLib.cpp
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
<<<<<<< HEAD:src/Window.cpp
=======
}

uint64_t getTime()
{
    return window->getTime();
}
>>>>>>> Dev:Src/WindowLib.cpp
}