//
// Created by luket on 25/04/2020.
//
#ifdef  __linux__
#include "X11Window.h"
#include<GL/glx.h>
#include <memory.h>
GLXContext              glc{};
void LunaLuxEngine::window_api::X11Window::createWindow(bool openGL)
{
    dpy = XOpenDisplay(nullptr);
    CHECK_P(dpy, "cannot connect to X server")

    if(openGL)
    {
        XVisualInfo             *vi{};
        Colormap                cmap{};

        vi = glXChooseVisual(dpy, 0, att);

        cmap = XCreateColormap(dpy, DefaultRootWindow(dpy), vi->visual, AllocNone);
        swa.colormap = cmap;
        swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;

        win = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, width, height, 0,vi->depth,InputOutput,vi->visual,
                            CWColormap | CWEventMask, &swa);

        XMapWindow(dpy, win);
        XStoreName(dpy, win, reinterpret_cast<const char*>(Title));

        glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
        glXMakeCurrent(dpy, win, glc);
    }
    else
    {
        win = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, width, height, 0, 0,InputOutput,nullptr,
                            ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask |CWEventMask, &swa);

        XMapWindow(dpy, win);
        XStoreName(dpy, win, reinterpret_cast<const char*>(Title));
    }
}

void LunaLuxEngine::window_api::X11Window::updateWindow(bool openGL)
{
    if(openGL) glXSwapBuffers(dpy, win);

    XNextEvent(dpy, &xev);

		switch (xev.type)
		{
		case Expose:
			fireResizeCallback(width, height);
			break;
		case ConfigureNotify:
			break;
			//TODO fix this error not fatal to running but will not shutdown engine correctly
			/* XIO:  fatal IO error 11 (Resource temporarily unavailable) on X server ":0"
			 * after 42 requests (42 known processed) with 0 events remaining.
			 */
		case DestroyNotify:
			WIN_SHOULD_CLOSE = true;
			break;
		}

}

void LunaLuxEngine::window_api::X11Window::updateTitle(int8 * title)
{
    XTextProperty tp;
    char *props[1];

    props[0] = strdup (reinterpret_cast<const char *>(title));
    if (0 == props[0])
    {
        return;
    }

    if (!XStringListToTextProperty (props, 1, &tp))
    {
        LOG("Failed to convert text property");
    }
    else
    {
        XSetWMName (dpy, win, &tp);
        XFree (tp.value);
    }

    free (props[0]);
}

void LunaLuxEngine::window_api::X11Window::destoryWindow(bool openGL)
{
    XDestroyWindow(dpy, win);
    XSync(dpy, false);
    XCloseDisplay(dpy);
}
#endif
