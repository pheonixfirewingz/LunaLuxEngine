#pragma once

#include <Common_Header.h>
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
#include <GLFW/glfw3.h>
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
#endif
#ifdef __linux__
    private:
        Display                 *dpy{};
        Window                  root{};
        XVisualInfo             *vi{};
        Colormap                cmap{};
        XSetWindowAttributes    swa{};
        Window                  win{};
        GLXContext              glc{};
        XWindowAttributes       gwa{};
        XEvent                  xev{};
#endif
protected:
    char* Title = (char*)"temp";
	int16 width = 800,  height = 600;
	CrossWindow* window = this;
public:
	bool WIN_SHOULD_CLOSE;
	CrossWindow* get();
	void createWindow();
	void setTitle(char*);
	bool shouldClose();
	void setShouldClose(bool);
	void updateWindow();
	void destoryWindow();
};
}