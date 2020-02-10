#include <cstdio>
#include <cstdlib>
#include "Window.h"
#include "Input.h"
using namespace LunaLuxEngine::Input;
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

	inline LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_CLOSE:
			sc_temp = LLEtrue
			break;
		case WM_MOUSEMOVE:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			if (pt.x >= 0 && pt.x < CWin->getWindowW() && pt.y >= 0 && pt.y < CWin->getWindowH())
				Input::Input::get()->setMousePos(pt.x,pt.y);
		}
		case WM_KEYDOWN:
			Input::Input::get()->setKey(wParam,1);
			break;
		case WM_KEYUP:
			Input::Input::get()->setKey(wParam,0);
			break;
		case WM_RBUTTONDOWN:
			Input::Input::get()->setButton(0,1);
			break;
		case WM_RBUTTONUP:
			Input::Input::get()->setButton(0,0);
			break;
		case WM_LBUTTONDOWN:
			Input::Input::get()->setButton(1,1);
			break;
		case WM_LBUTTONUP:
			Input::Input::get()->setButton(1,0);
			break;
		case WM_MBUTTONDOWN:
			Input::Input::get()->setButton(2,1);
			break;
		case WM_MBUTTONUP:
			Input::Input::get()->setButton(2,0);
			break;
		default:
           return DefWindowProc(hWnd, Msg, wParam, lParam);
		}
		return 0;
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

		RECT wr = {0, 0, 800, 600};
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

    if(dpy == nullptr)
    {
        std::printf("\n\tcannot connect to X server\n\n");
        std::exit(0);
    }

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

}
namespace LunaLuxEngine::Input
{
	LLEbool Input::isKeyDown(KeyCodes code)
	{
		if (keys[code] != 0) return LLEtrue
		else return LLEfalse
	}

	void Input::setKey(int32 code,LLEbool state)
	{
		keys[code] = state;
	}

	LLEbool Input::isMouseButtonDown(MouseButtons buttons)
	{
		if (M_buttons[buttons] != 0) return LLEtrue
		else return LLEfalse
	}

	void Input::setButton(int32 code, LLEbool state)
	{
		M_buttons[code] = state;
	}

	void Input::setMousePos(float x, float y)
	{
		M_posx = x;
		M_posy = y;
	}

	int32 Input::getPosX()
	{
		return (int32)M_posx;
	}

	int32 Input::getPosY()
	{
		return (int32)M_posy;
	}
}