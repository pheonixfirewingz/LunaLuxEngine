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
        inline HWND getWindow()
        {
            return hwnd;
        };
        LPCSTR class_name = (LPCSTR)"LunaLuxEngine_WindowClass";
#endif
#ifdef __linux__
    private:
        Display                 *dpy{};
        Window                  root{};
        Window                  win{};
        XEvent                  xev{};
        inline Display getDisplay()
        {
            return dpy;
        };

#endif
protected:
        char* Title = (char*)"temp";
        int16 width = 800,  height = 600;
public:
        bool WIN_SHOULD_CLOSE = false;
        void createWindow();
        inline void setTitle(char* intitle)
        {
            Title = intitle;
        };
        inline void setSize(int16 inwidth,int inheight)
        {
            width = inwidth;
            height = inheight;
        };
        inline char* getTitle()
        {
            return Title;
        };
        inline bool shouldClose()
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
	};
}