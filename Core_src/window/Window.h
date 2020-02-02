#pragma once

#include <LLESDK/Common_Header.h>
#ifdef WIN32
#include <Windows.h>
#define IDI_ICON1 101
#endif
#ifdef __linux__
#include<cstdio>
#include<thread>
#include<cstdlib>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/glx.h>
#endif
#ifdef MAC
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
#ifdef MAC
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
	bool shouldClose()
	{
		return  WIN_SHOULD_CLOSE;
	};
	void updateWindow();
	void destoryWindow();
	};
}