#pragma once
#include <LLESDK/types.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>
#include <windowsx.h>
#endif
#ifdef __linux__
#include <cstring>
#include <X11/X.h>
#include <X11/Xlib.h>
#endif
#define CWin LunaLuxEngine::window_api::CrossWindow::get()

namespace LunaLuxEngine::window_api
{
class CrossWindow
{
#ifdef WIN32
    private:
        HWND hwnd{};
        HINSTANCE Inst{};
        public:
        inline HWND getWindow()
        {
            return hwnd;
        };
        LPCSTR class_name = (LPCSTR)"LunaLuxEngine_WindowClass";
#endif
#ifdef  __linux__
private:
    Display                 *dpy{};
    Window                  root{};
    Window                  win{};
    XSetWindowAttributes    swa{};
    Colormap                cmap{};
    XEvent                  xev{};
public:
    inline Display* getWindowL()
    {
        return dpy;
    };

    inline Window getWindowL_()
    {
        return win;
    }
#endif
protected:
        int8* Title = (int8*)"temp";
        int16 width = 800,  height = 600;
        void(*resizeCallback)(int32,int32) = nullptr;
public:
        LLEbool WIN_SHOULD_CLOSE = LLEfalse;
        void createWindow();
        inline void setTitle(int8* in_title)
        {
            Title = in_title;
        };
        inline void setSize(int16 in_width,int in_height)
        {
            width = in_width;
            height = in_height;
            //fireResizeCallback(in_width, in_height);
        };
        inline int8* getTitle()
        {
            return Title;
        };
        inline LLEbool shouldClose()
        {
            return  WIN_SHOULD_CLOSE;
        };
        void updateWindow();
        void destoryWindow();

		inline float getWindowW()
        {
            return width;
        };
		inline float getWindowH()
		{
			return height;
		};
        inline void setResizeCallback(void(*callback)(int32, int32))
        {
            resizeCallback = callback;
        }
        void fireResizeCallback(int32, int32);

		inline static CrossWindow* get()
		{
			static auto* window_ = new CrossWindow();
			return window_;
		}
	};
}