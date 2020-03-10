#include <cstdio>
#include <cstdlib>
#include "Window.h"
#include <exception>
namespace LunaLuxEngine::window_api
{
#ifdef WIN32

	// Only funtion extenal from window that window requies to run (windows)
	inline LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		CWin.mouseHandler(Msg, wParam, lParam);
		CWin.keyboardHandler(Msg, wParam, lParam);
		CWin.commonHandler(Msg, wParam, lParam);
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	void CrossWindow::updateWindow()
	{
		if (!WIN_SHOULD_CLOSE)
		{
			MSG msg;
			GetMessage(&msg, nullptr, 0, 0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void CrossWindow::createWindow()
	{
		WIN_SHOULD_CLOSE = LLEfalse
			Inst = GetModuleHandle(nullptr);

		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = Inst;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.lpszClassName = class_name;

		RegisterClassEx(&wc);

		RECT wr = { 0, 0, width, height };
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

		hwnd = CreateWindowEx(NULL, class_name, reinterpret_cast<LPCSTR>(Title), WS_OVERLAPPEDWINDOW, 0, 0, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, Inst, nullptr);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
	}

	void CrossWindow::destoryWindow()
	{
		DestroyWindow(hwnd);
		UnregisterClassW((LPWSTR)class_name, Inst);
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