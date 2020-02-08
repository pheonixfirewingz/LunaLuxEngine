#include <chrono>
#include "Window.h"
#include "../LunaLuxEngineCore.h"

namespace LunaLuxEngine::window_api
{
    bool sc_temp;
#ifdef __linux__
    void CrossWindow::updateWindow()
    {
        XNextEvent(dpy, &xev);

        switch(xev.type)
        {
            case Expose:
                XGetWindowAttributes(dpy, win, &gwa);
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
        dpy = XOpenDisplay(nullptr);

        if(dpy == nullptr)
        {
            std::printf("\n\tcannot connect to X server\n\n");
            std::exit(0);
        }

        root = DefaultRootWindow(dpy);

        win = XCreateWindow(dpy, root, 0, 0, width, height, 0, nullptr, InputOutput, nullptr, CWColormap | CWEventMask,nullptr);

        XMapWindow(dpy, win);
		XSync(dpy, true);
        XStoreName(dpy, win, Title);
    }

    void CrossWindow::destoryWindow()
    {
        XDestroyWindow(dpy, win);
        XSync(dpy, false);
        XCloseDisplay(dpy);
    }
#endif
#ifdef WIN32
	void CrossWindow::updateWindow()
	{
		if (sc_temp) WIN_SHOULD_CLOSE = true;
		if (!WIN_SHOULD_CLOSE)
		{
			MSG msg;
			GetMessage(&msg, nullptr, 0, 0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	inline LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_CLOSE:
		{
			sc_temp = true;
		}
			break;
		default:
            		return DefWindowProc(hWnd, Msg, wParam, lParam);
            		break;
		}
		return 0;
	}

	void CrossWindow::createWindow()
	{
		WIN_SHOULD_CLOSE = false;
		Inst = GetModuleHandle(nullptr);

		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = Inst;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		//wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = class_name;

		RegisterClassEx(&wc);

		RECT wr = {0, 0, 800, 600};
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

		hwnd = CreateWindowEx(NULL,class_name,Title,WS_OVERLAPPEDWINDOW,300,300,wr.right - wr.left,wr.bottom - wr.top,nullptr,nullptr,Inst,nullptr);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
	}

	void CrossWindow::destoryWindow()
	{
		DestroyWindow(hwnd);
		UnregisterClassW((LPWSTR)class_name, Inst);
	}
#endif
}