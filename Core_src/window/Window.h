#pragma once

#include <LLESDK/Common_Header.h>
#ifdef WIN32
#include <windows.h>
#include <windowsx.h>
#endif
#ifdef __linux__
#include<cstdio>
#include<thread>
#include<cstdlib>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/glx.h>
#endif
namespace LunaLuxEngine::window_api
{

class CrossWindow
{
#ifdef WIN32
    private:
        HWND hwnd{};
        HINSTANCE Inst{};
        public:
        HWND getWindow();
        LPCSTR class_name = (LPCSTR)"LunaLuxEngine_WindowClass";
#endif
#ifdef __linux__
    private:
        Display                 *dpy{};
        Window                  root{};
        XVisualInfo             *vi{};
        Colormap                cmap{};
        XSetWindowAttributes    swa{};
        Window                  win{};
        XWindowAttributes       gwa{};
        XEvent                  xev{};
#endif
protected:
        char* Title = (char*)"temp";
        int16 width = 800,  height = 600;
public:
        bool WIN_SHOULD_CLOSE = false;
        void createWindow();
        void setTitle(char* intitle)
        {
            Title = intitle;
        };
        void setSize(int16 inwidth,int inheight)
        {
            width = inwidth;
            height = inheight;
        };
        char* getTitle()
        {
            return Title;
        };
        bool shouldClose()
        {
            return  WIN_SHOULD_CLOSE;
        };
        void updateWindow();
        void destoryWindow();

		float getWindowW();
		float getWindowH();
	};
}