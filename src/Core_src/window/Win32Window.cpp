#ifdef WIN32

#include <Windows.h>
#include "Win32Window.h"
#include "Window.h"

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
		CWin.getNativeWindow()->fireResizeCallback(MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y);
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

void LunaLuxEngine::window_api::Win32Window::createWindow()
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
}

void LunaLuxEngine::window_api::Win32Window::destoryWindow()
{
	DestroyWindow(hwnd);
	UnregisterClassW((LPWSTR)class_name, Inst);
}

void LunaLuxEngine::window_api::Win32Window::updateTitle(int8 * in)
{
    SetWindowTextA(hwnd,reinterpret_cast<LPCSTR>(in));
}

#endif