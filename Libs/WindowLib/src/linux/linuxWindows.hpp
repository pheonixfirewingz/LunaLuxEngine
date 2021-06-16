#pragma once
//
// Created by digitech on 15/03/2021.
//
//TODO: add documentation.
#include<X11/X.h>
#include<X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xutil.h>
#include "../IO.hpp"
#include<GL/glx.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <tuple>

namespace LunaLux
{

    struct InfoRet
    {
    public:
        Display* dpy;Window* win;XVisualInfo* vi;
        InfoRet(Display *pDisplay, Window* i, XVisualInfo *ptr) :dpy(pDisplay),win(i),vi(ptr) {}
    };

    class LinuxWindow
    {
    private:
        Display*                dpy{};
        Window                  win{};
        XVisualInfo*            vi{};
        bool shouldClose{false};
    public:
        static std::unique_ptr<IO> io;

        explicit LinuxWindow(const char *title, const int width, const int height)
        {
            dpy = XOpenDisplay(nullptr);
            io = std::make_unique<IO>();
            int atr[] = { 4, 12, 24, 5, 0L };
            vi = glXChooseVisual(dpy, 0, atr);
            XSetWindowAttributes info;
            info.colormap = XCreateColormap(dpy, DefaultRootWindow(dpy), vi->visual, AllocNone);
            info.event_mask = ExposureMask | VisibilityChangeMask | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask;
            win = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, width, height, 0,vi->depth,InputOutput,vi->visual,CWColormap | CWEventMask, &info);
            XMapWindow(dpy, win);
            XStoreName(dpy, win, reinterpret_cast<const char*>(title));
        }

        std::unique_ptr<LunaLux::IO> getIO()
        { return std::move(io); }

        InfoRet* GetNativeWindow()
        {
            static auto* infoRet = new InfoRet(dpy,&win,vi);
            return infoRet;
        }

        void ChangeWindowTitle(const char *string)
        {
            XTextProperty tp;
            char *props[1];

            props[0] = strdup (reinterpret_cast<const char *>(string));

            if (nullptr == props[0]) return;

            if (!XStringListToTextProperty (props, 1, &tp))
                printf("[LunaLuxWindowLib] ERROR:Failed to convert text property");
            else
            {
                XSetWMName (dpy, win, &tp);
                XFree (tp.value);
            }

            free(props[0]);
        }

        [[nodiscard]] bool ShouldClose() const
        {
            return shouldClose;
        }

        std::tuple<int, int> GetWindowSize()
        {
            XWindowAttributes info;
            XGetWindowAttributes(dpy,win,&info);
            //returns the width and height from the x window info
            return {info.width,info.height};
        }

        void Update()
        {
            XEvent xev{};
            XNextEvent(dpy, &xev);

            switch (xev.type)
            {
                case Expose:
                case ConfigureNotify: break;
                case DestroyNotify:
                    shouldClose = true;
                    break;
            }
        }

        void Close()
        {
            XDestroyWindow(dpy, win);
            XSync(dpy, false);
            XCloseDisplay(dpy);
            XSync(dpy, false);
        }

        uint64_t getTime()
        {
            return 0;
        }
    };

}