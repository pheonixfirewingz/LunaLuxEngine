#include <cstdio>
#include <cstdlib>
#include "Window.h"
#include <exception>
//TODO: find out why when the mouse moves the program raidly eats memory?
namespace LunaLuxEngine::window_api
{
#ifdef WIN32
    LLEbool sc_temp;
	void CrossWindow::updateWindow()
	{
		if (sc_temp) WIN_SHOULD_CLOSE = LLEtrue;
		if (!WIN_SHOULD_CLOSE)
		{
			MSG msg;
			GetMessage(&msg, nullptr, 0, 0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	bool in_win = true;
	inline LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
			case WM_CLOSE:
				sc_temp = LLEtrue;
			break;
			case WM_SIZE:
			{
				POINTS pt = MAKEPOINTS(lParam);
				CWin->fireResizeCallback(pt.x, pt.y);
				break;
			}
			case WM_MOUSEHOVER:
				in_win = true;
			case WM_MOUSELEAVE:
				in_win = false;
			case WM_MOUSEMOVE:
			{
				if (in_win)
				{
					CWin->M_posx = ((DWORD_PTR)(lParam)) & 0xffff;
					CWin->M_posy = (((DWORD_PTR)(lParam)) >> 16) & 0xffff;
				}
			}
			case WM_KEYDOWN:
				CWin->setKey(wParam,1);
				break;
			case WM_KEYUP:
				CWin->setKey(wParam,0);
				break;
			case WM_RBUTTONDOWN:
				CWin->setButton(0,1);
				break;
			case WM_RBUTTONUP:
				CWin->setButton(0,0);
				break;
			case WM_LBUTTONDOWN:
				CWin->setButton(1,1);
				break;
			case WM_LBUTTONUP:
				CWin->setButton(1,0);
				break;
			case WM_MBUTTONDOWN:
				CWin->setButton(2,1);
				break;
			case WM_MBUTTONUP:
				CWin->setButton(2,0);
				break;
			default:
			   return DefWindowProc(hWnd, Msg, wParam, lParam);
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

		RECT wr = {0, 0, width, height};
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

		hwnd = CreateWindowEx(NULL,class_name, reinterpret_cast<LPCSTR>(Title),WS_OVERLAPPEDWINDOW,300,300, wr.right - wr.left, wr.bottom - wr.top,nullptr,nullptr,Inst,nullptr);

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

    switch(xev.type)
    {
        case Expose:
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
    CHECK_P(dpy,"cannot connect to X server")
    root = DefaultRootWindow(dpy);
    swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
    win = XCreateWindow(dpy, root, 0, 0, width, height, 0, CopyFromParent , InputOutput, CopyFromParent ,CWEventMask,&swa);
    XMapWindow(dpy, win);
    XStoreName(dpy, win, reinterpret_cast<const char *>(Title));
}

void CrossWindow::destoryWindow()
{
    XDestroyWindow(dpy, win);
    XSync(dpy, false);
    XCloseDisplay(dpy);
}
#endif
	void CrossWindow::fireResizeCallback(int32 in_width, int32 in_height)
	{
		if(resizeCallback != nullptr)
			resizeCallback(in_width, in_height);
	}
}