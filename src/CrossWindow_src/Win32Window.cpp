#ifdef WIN32

#include <Windows.h>
#include "Win32Window.h"
#include "Window.h"
#include "../Core_src/common/EnginePanic.h"

bool in_win = true;
inline void MH(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_MOUSEHOVER:
		in_win = true;
		break;

	case WM_MOUSELEAVE:
		in_win = false;
		break;

	case WM_MOUSEMOVE:
		if (in_win)
			CWin.getNativeWindow()->getInputController()->setMousePos((((DWORD_PTR)(lParam)) & 0xffff), ((((DWORD_PTR)(lParam)) >> 16) & 0xffff));
		break;

	case WM_RBUTTONDOWN:
		CWin.getNativeWindow()->getInputController()->setButton(0, 1);
		break;

	case WM_RBUTTONUP:
		CWin.getNativeWindow()->getInputController()->setButton(0, 0);
		break;

	case WM_LBUTTONDOWN:
		CWin.getNativeWindow()->getInputController()->setButton(1, 1);
		break;

	case WM_LBUTTONUP:
		CWin.getNativeWindow()->getInputController()->setButton(1, 0);
		break;

	case WM_MBUTTONDOWN:
		CWin.getNativeWindow()->getInputController()->setButton(2, 1);
		break;

	case WM_MBUTTONUP:
		CWin.getNativeWindow()->getInputController()->setButton(2, 0);
		break;

	default:
		break;
	}
}
inline LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CLOSE:
		CWin.setShouldClose(1);
		break;
	case WM_SIZE:
		CWin.getNativeWindow()->setSize(MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y);
		break;
	case WM_KEYDOWN:
		CWin.getNativeWindow()->getInputController()->setKey(wParam, 1);
		break;
	case WM_KEYUP:
		CWin.getNativeWindow()->getInputController()->setKey(wParam, 0);
		break;
	default:
		break;
	}
	MH(Msg, wParam, lParam);
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void LunaLuxEngine::window_api::Win32Window::createWindow(bool OpenGL)
{
	WIN_SHOULD_CLOSE = LLEfalse;
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

    MoveWindow(hwnd, GetSystemMetrics(SM_CXSCREEN) / 12, GetSystemMetrics(SM_CYSCREEN) / 12, wr.right - wr.left, wr.bottom - wr.top, true);

    if(OpenGL)
    {
        PIXELFORMATDESCRIPTOR pfd =
                {
                        sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
                        24,0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
                };
        SetPixelFormat(GetDC(hwnd), ChoosePixelFormat(GetDC(hwnd), &pfd), &pfd);
        rc = wglCreateContext(GetDC(hwnd));
        wglMakeCurrent(GetDC(hwnd), rc);
    }
}

void LunaLuxEngine::window_api::Win32Window::destoryWindow(bool openGL)
{
    if(openGL)
    {
        ReleaseDC(hwnd, GetDC(hwnd));
        wglDeleteContext(rc);
    }
	DestroyWindow(hwnd);
	UnregisterClassW((LPWSTR)class_name, Inst);
}

void LunaLuxEngine::window_api::Win32Window::updateTitle(int8 * in)
{
    SetWindowTextA(hwnd,reinterpret_cast<LPCSTR>(in));
}
void LunaLuxEngine::window_api::Win32Window::updateWindow(bool openGL)
{
    if (!shouldClose())
    {
#ifdef LLE_XBOX
        if (getInputController()->xbox_controller->isConnected())
        {
            if (getInputController()->xbox_controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
            {
                LOG("pressing g-pad a")
            }
            if (getInputController()->xbox_controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
            {
                LOG("pressing g-pad y")
            }
            if (getInputController()->xbox_controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
            {
                LOG("pressing g-pad b")
            }
            if (getInputController()->xbox_controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
            {
                LOG("pressing g-pad x")
            }
        }
        else LOG("Controller not found")
#endif
        RECT rect;
        GetWindowRect(hwnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        setSize(width,height);

        if(openGL) SwapBuffers(GetDC(hwnd));

        MSG msg;
        GetMessage(&msg, nullptr, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif