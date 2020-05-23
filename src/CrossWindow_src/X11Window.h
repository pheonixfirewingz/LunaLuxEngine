//
// Created by luket on 25/04/2020.
//
#ifndef LUNALUXENGINE_X11WINDOW_H
#define LUNALUXENGINE_X11WINDOW_H
#include "IWindow.h"
#ifdef __linux__
#include<X11/X.h>
#include<X11/Xlib.h>
#endif
namespace LunaLuxEngine::window_api
{
#ifdef __linux__
    class X11Window : public IWindow
    {
    private:
        int                     att[5] = { 4, 12, 24, 5, 0L };
        Display*                dpy{};
        Window                  root{};
        Window                  win{};
        XSetWindowAttributes    swa{};
        Colormap                cmap{};
        XEvent                  xev{};
    public:
        void createWindow() override;
        void updateWindow() override;
        void updateTitle(int8*) override;
        void destoryWindow() override;
        Display* getDis()
        {
            return dpy;
        }
    };
#else
    class X11Window : public IWindow
	{
	public:
		void createWindow() override {};
		void updateWindow() override {};
		void updateTitle(int8*) override {};
		void destoryWindow() override {};
	};
#endif
}
#endif
