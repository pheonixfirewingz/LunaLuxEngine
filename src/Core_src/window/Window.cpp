#include <cstdio>
#include <cstdlib>
#include "Window.h"
#include <exception>
namespace LunaLuxEngine::window_api
{
	void CrossWindow::setWindowType(WindowType type)
	{
		if (type == WindowType::Win32Window) window = new Win32Window();
	}
#ifdef WIN32
	void CrossWindow::updateWindow()
	{
		if (!window->shouldClose())
		{
			MSG msg;
			GetMessage(&msg, nullptr, 0, 0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
#endif
#ifdef __linux__
	void CrossWindow::updateWindow()
	{
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
			 * after 45 requests (45 known processed) with 0 events remaining.
			 */
		case DestroyNotify:
			WIN_SHOULD_CLOSE = true;
			break;
		}
	}

	void CrossWindow::createWindow()
	{
		XInitThreads();
		dpy = XOpenDisplay(nullptr);
		CHECK_P(dpy, "cannot connect to X server")
			root = DefaultRootWindow(dpy);
		vi = glXChooseVisual(dpy, 0, att);

		if (vi == NULL) FOURCE_STOP("\n\tno appropriate visual found\n\n")

			cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
		swa.colormap = cmap;
		swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
		win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
		XMapWindow(dpy, win);
		XStoreName(dpy, win, reinterpret_cast<const char*>(Title));
	}

	void CrossWindow::destoryWindow()
	{
		XDestroyWindow(dpy, win);
		XSync(dpy, false);
		XCloseDisplay(dpy);
	}
#endif
}