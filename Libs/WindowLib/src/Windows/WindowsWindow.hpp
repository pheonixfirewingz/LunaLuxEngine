#pragma once
//
// Created by luket on 08/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#if __has_include(<windows.h>)
/*--------------------------------------------------------------------------------------------
 * the WindowsWindow header is used to defined the abstract window function for the win32 API.
 *---------------------------------------------------------------------------------------------
 */
#    ifndef WIN32_LEAN_AND_MEAN
#        define WIN32_LEAN_AND_MEAN
#    endif
#    include "../IO.hpp"
#    include <cassert>
#    include <memory>
#    include <windows.h>
// this is defined to stop the compiler including legacy things like tape support
// NOTE:I don't know why it's still apart of the windows api as their not used in modern machines
// TODO: write documentation
namespace LunaLux
{
class WindowsWindow
{
  private:
    // this used to store the window id.
    HWND window_handler{nullptr};
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
    LARGE_INTEGER StartFrameTime{0}, Frequency{0};
    static void cleanUp();

  public:
    static void size(int width, int height) noexcept;

    static std::unique_ptr<LunaLux::IO> getIO();

    WindowsWindow(const char *title, const int width, const int height) noexcept
    {
        size(width, height);
        // this is required to tell windows that the application wants compositor server messages
        //=================================================================================================================
        // this is where we create the struct used to register our window to the windows compositor
        // struct documentation https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa
        WNDCLASSEX wc;
        // I dont know why we need to zero the memory used my the struct but if we don't the window will not be created.
        ZeroMemory(&wc, sizeof(WNDCLASSEX));
        // this is to tell the class the size of the struct going to be used to register
        wc.cbSize = sizeof(WNDCLASSEX);
        // Modify the window to have no background
        wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
        // this is were where we tell the windows compositor class the pointer to our windows message processing
        // function.
        wc.lpfnWndProc = WndProc;
        // this is used to tell the the compositor class the pointer to our win32 program instance.
        // function documentation
        // https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlea
        wc.hInstance = GetModuleHandle(nullptr);
        // this is used to tell the compositor what arrow to draw while the arrow is in the window
        // function documentation https://docs.microsoft.com/en-us/windows/win32/devnotes/-loadcursor
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        // this is where we define the class name so the compositor server can keep
        //  track and process window messages and data
        wc.lpszClassName = "LunaLuxWindowClass";
        // we use this function to register the struct to the compositor to create the server end window class
        // function documentation https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexa
        RegisterClassEx(&wc);
        //=================================================================================================================
        // this is where the window is created
        //=================================================================================================================
        // now using the function below we pass in our compositor server side class, the window title to be displayed,
        // some flags, rectangle top left point, rectangle bottom right point, and our win32 program instance. the null
        // and nullptr arguments can be looked up here
        // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
        window_handler = CreateWindowEx(0, "LunaLuxWindowClass", title, WS_OVERLAPPEDWINDOW, 0, 0, width, height,
                                        nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
        //=================================================================================================================
        // this is where we show and center the window on the screen
        //=================================================================================================================
        // we tell the compositor server to start painting the window on the screen
        // function documentation https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
        ShowWindow(window_handler, SW_SHOWDEFAULT);
        // now we tell the compositor server to move the window to the middle of the screen.
        // function documentation https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-movewindow
        MoveWindow(window_handler, GetSystemMetrics(SM_CXSCREEN) / 12, GetSystemMetrics(SM_CYSCREEN) / 12, width,
                   height, true);
        //=================================================================================================================
        // this is used to set up time functions
        //=================================================================================================================

        if (QueryPerformanceFrequency(&Frequency) == TRUE)
        {
            QueryPerformanceCounter(&StartFrameTime);
        }
        else
        {
            (void)(_wassert(_CRT_WIDE("normal system clock not available"), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0);
        }
    }
    void Update() noexcept
    {
        // create message to be processed
        MSG msg;
        // get message without waiting for message
        // function documentation https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea
        PeekMessage(&msg, window_handler, 0, 0, PM_REMOVE);
        /*if the message is null the this function just returns
         * else it translates the message for processing
         */
        // function documentation https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-translatemessage
        TranslateMessage(&msg);
        // this function sends the translated message back to window to send it to
        // the WinProc function with the args for that massage to be processed
        // function documentation https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-dispatchmessage
        DispatchMessage(&msg);
    }

    void Close() noexcept
    {
        // this function tells windows to close and destroy the compositor window
        // function documentation https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow
        DestroyWindow(window_handler);
        // this function is used to destory the class that handles the windows messages for the compositor window
        // function documentation https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-unregisterclassa
        UnregisterClassW(L"LunaLuxWindowClass", GetModuleHandle(nullptr));
        cleanUp();
    }

    HWND GetNativeWindow() noexcept
    {
        // this is used to return the current native window
        return window_handler;
    }

    void ChangeWindowTitle(const char *string) noexcept
    {
        SetWindowTextA(window_handler, string);
    }

    static bool ShouldClose() noexcept;

    static std::tuple<int, int> GetWindowSize() noexcept;

    uint64_t getTime()
    {

        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);

        now.QuadPart -= StartFrameTime.QuadPart;
        now.QuadPart *= 1.0e9;
        now.QuadPart /= Frequency.QuadPart;

        return now.QuadPart;
    }
};
} // namespace LunaLux
#endif