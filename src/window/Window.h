#pragma once
#include "../Common_Header.h"
#ifdef WIN32
/*
 * The following #defines disable a bunch of unused windows stuff
 * removing some or all of these defines it will increase build time.
 */
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#define STRICT
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