//
// Created by luket on 25/04/2020.
//
#ifdef  __linux__
#include "X11Window.h"
#include<GL/glx.h>
XVisualInfo             *vi{};
GLXContext              glc{};
void LunaLuxEngine::window_api::X11Window::createWindow()
{
    XInitThreads();
    dpy = XOpenDisplay(nullptr);
    CHECK_P(dpy, "cannot connect to X server")
    root = DefaultRootWindow(dpy);
    vi = glXChooseVisual(dpy, 0, att);

    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
    win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    XMapWindow(dpy, win);
    XStoreName(dpy, win, reinterpret_cast<const char*>(Title));
    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);
}

void LunaLuxEngine::window_api::X11Window::updateWindow()
{
    glXSwapBuffers(dpy, win);
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

}

void LunaLuxEngine::window_api::X11Window::destoryWindow()
{
    XDestroyWindow(dpy, win);
    XSync(dpy, false);
    XCloseDisplay(dpy);
}
#endif
