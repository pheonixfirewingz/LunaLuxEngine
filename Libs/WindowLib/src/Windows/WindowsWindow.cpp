// Created by luket on 05/12/2020.
#include "WindowsWindow.hpp"
#if __has_include(<windows.h>)
//this is used to say if the window should close
static bool ShouldCloseBool{false};
bool in_win{true};
//they are to store the current window size
static int width_store, height_store;

static std::unique_ptr<LunaLux::IO> io = std::make_unique<LunaLux::IO>();

void LunaLux::WindowsWindow::cleanUp()
{
    //this is to release the io handler after window is closed
    (void)io.release();
}

std::unique_ptr<LunaLux::IO> LunaLux::WindowsWindow::getIO()
{ return std::move(io); }

 void LunaLux::WindowsWindow::size(const int width, const int height) noexcept
{
    //storing the initial width and height into local memory
    width_store = width;
    height_store = height;
}

 std::tuple<int, int> LunaLux::WindowsWindow::GetWindowSize() noexcept
 {
     //returns the width and height from local storage
     return { width_store,height_store };
 }

bool LunaLux::WindowsWindow::ShouldClose() noexcept
{
    // returns true close window else returns false close it
    return ShouldCloseBool;
}

LRESULT CALLBACK LunaLux::WindowsWindow::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        //if the message ID is WM_CLOSE or 0x0010 we set the ShouldCloseBool atomic boolean to true
        case WM_CLOSE:
            ShouldCloseBool = true;
            break;
        case WM_DEVICECHANGE:
            if(wParam == 0x0007) io->Reset();
            break;
        case WM_SIZE:
            WindowsWindow::size(MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y);
            break;
        //if the message ID is WM_KEYDOWN or 0x0100 we call the Keyboard setKeyState function
        case WM_KEYDOWN:
            io->setButton(wParam,true);
            break;
        //if the message ID is WM_KEYUP or 0x0101 we call the Keyboard setKeyState function
        case WM_KEYUP:
            io->setButton(wParam, false);
            break;
            //if the message ID is WM_LBUTTONDOWN or 0x0201 we call the Mouse setMouseState function
        case WM_LBUTTONDOWN:
            io->setButton(257, true);
            break;
            //if the message ID is WM_LBUTTONUP or 0x0202 we call the Mouse setMouseState function
        case WM_LBUTTONUP:
            io->setButton(257, false);
            break;
            //if the message ID is WM_RBUTTONDOWN or 0x0204 we call the Mouse setMouseState function
        case WM_RBUTTONDOWN:
            io->setButton(258, true);
            break;
            //if the message ID is WM_RBUTTONUP or 0x0205 we call the Mouse setMouseState function
        case WM_RBUTTONUP:
            io->setButton(258, false);
            break;
            //if the message ID is WM_MBUTTONDOWN or 0x0207 we call the Mouse setMouseState function
        case WM_MBUTTONDOWN:
            io->setButton(259, true);
            break;
            //if the message ID is WM_MBUTTONUP or 0x0208 we call the Mouse setMouseState function
        case WM_MBUTTONUP:
            io->setButton(259, false);
            break;
        case WM_MOUSEHOVER:
            // sets bool true if mouse is in window
            in_win = true;
            break;
        case WM_MOUSELEAVE:
            // sets bool false if mouse is in window
            in_win = false;
            break;
        case WM_MOUSEWHEEL:
            // we use this to set the mouse scroll wheel
            io->setWheelDelta((((wParam) >> 16) & 0xffff));
            break;

        case WM_MOUSEMOVE:
            if (in_win)
                io->setPosition({(lParam & 0xffff), ((lParam >> 16) & 0xffff)});
            break;
        default:
            break;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
#endif