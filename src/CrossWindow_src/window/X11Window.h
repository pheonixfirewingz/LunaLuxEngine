//
// Created by luket on 25/04/2020.
//
#ifndef LUNALUXENGINE_X11WINDOW_H
#define LUNALUXENGINE_X11WINDOW_H
#include "IWindow.h"
#ifdef LLE_LINUX
#include<X11/X.h>
#include<X11/Xlib.h>
#include <X11/Xutil.h>
#endif
namespace LunaLuxEngine::window_api
{
#ifdef __linux__
    class X11Window : public IWindow
    {
    private:
        int                     att[5] = { 4, 12, 24, 5, 0L };
        Display*                dpy{};
        Window                  win{};
        XSetWindowAttributes    swa{};
        XEvent                  xev{};


    public:
        void createWindow(bool) override;
        void updateWindow(bool) override;
        void updateTitle(int8*) override;
        void destoryWindow(bool) override;
        Display* getDis()
        {
            return dpy;
        }

        Window getWin()
        {
            return win;
        }
    };
#else
    class X11Window : public IWindow
	{
	public:
		void createWindow(bool) override {};
		void updateWindow(bool) override {};
		void updateTitle(int8*) override {};
		void destoryWindow(bool) override {};
	};
#endif
}
#endif
