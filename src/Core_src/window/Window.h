#pragma once
#include <LLESDK/types.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>
#include <windowsx.h>
#endif
#ifdef __linux__
#include <cstring>
#include <X11/X.h>
#include <X11/Xlib.h>
#include "Opengl_h.h"
#endif
#define CWin LunaLuxEngine::window_api::CrossWindow::get()

extern "C"
{
#ifdef WIN32
	//KeyCodes with the value 0x00 are unknown keycodes
	enum KeyCodes
	{
		LLE_KEY_0 = 0x30,
		LLE_KEY_1 = 0x31,
		LLE_KEY_2 = 0x32,
		LLE_KEY_3 = 0x33,
		LLE_KEY_4 = 0x34,
		LLE_KEY_5 = 0x35,
		LLE_KEY_6 = 0x36,
		LLE_KEY_7 = 0x37,
		LLE_KEY_8 = 0x38,
		LLE_KEY_9 = 0x39,
		LLE_KEY_A = 0x41,
		LLE_KEY_B = 0x42,
		LLE_KEY_C = 0x43,
		LLE_KEY_D = 0x44,
		LLE_KEY_E = 0x45,
		LLE_KEY_F = 0x46,
		LLE_KEY_G = 0x47,
		LLE_KEY_H = 0x48,
		LLE_KEY_I = 0x49,
		LLE_KEY_J = 0x4A,
		LLE_KEY_K = 0x4B,
		LLE_KEY_L = 0x4C,
		LLE_KEY_M = 0x4D,
		LLE_KEY_N = 0x4E,
		LLE_KEY_O = 0x4F,
		LLE_KEY_P = 0x50,
		LLE_KEY_Q = 0x51,
		LLE_KEY_R = 0x52,
		LLE_KEY_S = 0x53,
		LLE_KEY_T = 0x54,
		LLE_KEY_U = 0x55,
		LLE_KEY_V = 0x56,
		LLE_KEY_W = 0x57,
		LLE_KEY_X = 0x58,
		LLE_KEY_Y = 0x59,
		LLE_KEY_Z = 0x5A,
		LLE_KEY_APOSTROPHE = 0x00,
		LLE_KEY_BACKSLASH = 0x00,
		LLE_KEY_COMMA = 0x00,
		LLE_KEY_EQUAL = 0x00,
		LLE_KEY_GRAVE_ACCENT = 0x00,
		LLE_KEY_LEFT_BRACKET = 0x00,
		LLE_KEY_MINUS = 0x00,
		LLE_KEY_PERIOD = 0x00,
		LLE_KEY_RIGHT_BRACKET = 0x00,
		LLE_KEY_SEMICOLON = 0x00,
		LLE_KEY_SLASH = 0x00,
		LLE_KEY_WORLD_2 = 0x00,
		LLE_KEY_BACKSPACE = 0x08,
		LLE_KEY_DELETE = 0x00,
		LLE_KEY_END = 0x24,
		LLE_KEY_ENTER = 0x0D,
		LLE_KEY_ESCAPE = 0x1B,
		LLE_KEY_HOME = 0x00,
		LLE_KEY_INSERT = 0x00,
		LLE_KEY_MENU = 0x00,
		LLE_KEY_PAGE_DOWN = 0x22,
		LLE_KEY_PAGE_UP = 0x21,
		LLE_KEY_PAUSE = 0x00,
		LLE_KEY_SPACE = 0x20,
		LLE_KEY_TAB = 0x09,
		LLE_KEY_CAPS_LOCK = 0x14,
		LLE_KEY_NUM_LOCK = 0x90,
		LLE_KEY_SCROLL_LOCK = 0x91,
		LLE_KEY_F1 = 0x70,
		LLE_KEY_F2 = 0x71,
		LLE_KEY_F3 = 0x72,
		LLE_KEY_F4 = 0x73,
		LLE_KEY_F5 = 0x74,
		LLE_KEY_F6 = 0x75,
		LLE_KEY_F7 = 0x76,
		LLE_KEY_F8 = 0x77,
		LLE_KEY_F9 = 0x78,
		LLE_KEY_F10 = 0x79,
		LLE_KEY_F11 = 0x7A,
		LLE_KEY_F12 = 0x7B,
		LLE_KEY_F13 = 0x7C,
		LLE_KEY_F14 = 0x7D,
		LLE_KEY_F15 = 0x7E,
		LLE_KEY_F16 = 0x7F,
		LLE_KEY_F17 = 0x80,
		LLE_KEY_F18 = 0x81,
		LLE_KEY_F19 = 0x82,
		LLE_KEY_F20 = 0x83,
		LLE_KEY_F21 = 0x84,
		LLE_KEY_F22 = 0x85,
		LLE_KEY_F23 = 0x86,
		LLE_KEY_F24 = 0x87,
		LLE_KEY_LEFT_ALT = 0x00,
		LLE_KEY_LEFT_CONTROL = 0xA2,
		LLE_KEY_LEFT_SHIFT = 0xA0,
		LLE_KEY_LEFT_SUPER = 0x00,
		LLE_KEY_PRINT_SCREEN = 0x2C,
		LLE_KEY_RIGHT_ALT = 0x00,
		LLE_KEY_RIGHT_CONTROL = 0xA3,
		LLE_KEY_RIGHT_SHIFT = 0xA1,
		LLE_KEY_RIGHT_SUPER = 0x00,
		LLE_KEY_DOWN = 0x28,
		LLE_KEY_LEFT = 0x25,
		LLE_KEY_RIGHT = 0x27,
		LLE_KEY_UP = 0x26,
		LLE_KEY_KP_0 = 0x60,
		LLE_KEY_KP_1 = 0x61,
		LLE_KEY_KP_2 = 0x62,
		LLE_KEY_KP_3 = 0x63,
		LLE_KEY_KP_4 = 0x64,
		LLE_KEY_KP_5 = 0x65,
		LLE_KEY_KP_6 = 0x66,
		LLE_KEY_KP_7 = 0x67,
		LLE_KEY_KP_8 = 0x68,
		LLE_KEY_KP_9 = 0x69,
		LLE_KEY_KP_ADD = 0x6B,
		LLE_KEY_KP_DECIMAL = 0x6E,
		LLE_KEY_KP_DIVIDE = 0x6F,
		LLE_KEY_KP_ENTER = 0x00,
		LLE_KEY_KP_EQUAL = 0x00,
		LLE_KEY_KP_MULTIPLY = 0x6A,
		LLE_KEY_KP_SUBTRACT = 0x6D
	};
#endif
#ifdef __linux__
	//KeyCodes with the value 0x00 are unknown keycodes
	enum KeyCodes
	{
		LLE_KEY_0 = 0x00,
		LLE_KEY_1 = 0x00,
		LLE_KEY_2 = 0x00,
		LLE_KEY_3 = 0x00,
		LLE_KEY_4 = 0x00,
		LLE_KEY_5 = 0x00,
		LLE_KEY_6 = 0x00,
		LLE_KEY_7 = 0x00,
		LLE_KEY_8 = 0x00,
		LLE_KEY_9 = 0x00,
		LLE_KEY_A = 0x00,
		LLE_KEY_B = 0x00,
		LLE_KEY_C = 0x00,
		LLE_KEY_D = 0x00,
		LLE_KEY_E = 0x00,
		LLE_KEY_F = 0x00,
		LLE_KEY_G = 0x00,
		LLE_KEY_H = 0x00,
		LLE_KEY_I = 0x00,
		LLE_KEY_J = 0x00,
		LLE_KEY_K = 0x00,
		LLE_KEY_L = 0x00,
		LLE_KEY_M = 0x00,
		LLE_KEY_N = 0x00,
		LLE_KEY_O = 0x00,
		LLE_KEY_P = 0x00,
		LLE_KEY_Q = 0x00,
		LLE_KEY_R = 0x00,
		LLE_KEY_S = 0x00,
		LLE_KEY_T = 0x00,
		LLE_KEY_U = 0x00,
		LLE_KEY_V = 0x00,
		LLE_KEY_W = 0x00,
		LLE_KEY_X = 0x00,
		LLE_KEY_Y = 0x00,
		LLE_KEY_Z = 0x00,
		LLE_KEY_APOSTROPHE = 0x00,
		LLE_KEY_BACKSLASH = 0x00,
		LLE_KEY_COMMA = 0x00,
		LLE_KEY_EQUAL = 0x00,
		LLE_KEY_GRAVE_ACCENT = 0x00,
		LLE_KEY_LEFT_BRACKET = 0x00,
		LLE_KEY_MINUS = 0x00,
		LLE_KEY_PERIOD = 0x00,
		LLE_KEY_RIGHT_BRACKET = 0x00,
		LLE_KEY_SEMICOLON = 0x00,
		LLE_KEY_SLASH = 0x00,
		LLE_KEY_WORLD_2 = 0x00,
		LLE_KEY_BACKSPACE = 0x00,
		LLE_KEY_DELETE = 0x00,
		LLE_KEY_END = 0x00,
		LLE_KEY_ENTER = 0x00,
		LLE_KEY_ESCAPE = 0x00,
		LLE_KEY_HOME = 0x00,
		LLE_KEY_INSERT = 0x00,
		LLE_KEY_MENU = 0x00,
		LLE_KEY_PAGE_DOWN = 0x00,
		LLE_KEY_PAGE_UP = 0x00,
		LLE_KEY_PAUSE = 0x00,
		LLE_KEY_SPACE = 0x00,
		LLE_KEY_TAB = 0x00,
		LLE_KEY_CAPS_LOCK = 0x00,
		LLE_KEY_NUM_LOCK = 0x00,
		LLE_KEY_SCROLL_LOCK = 0x00,
		LLE_KEY_F1 = 0x00,
		LLE_KEY_F2 = 0x00,
		LLE_KEY_F3 = 0x00,
		LLE_KEY_F4 = 0x00,
		LLE_KEY_F5 = 0x00,
		LLE_KEY_F6 = 0x00,
		LLE_KEY_F7 = 0x00,
		LLE_KEY_F8 = 0x00,
		LLE_KEY_F9 = 0x00,
		LLE_KEY_F10 = 0x00,
		LLE_KEY_F11 = 0x00,
		LLE_KEY_F12 = 0x00,
		LLE_KEY_F13 = 0x00,
		LLE_KEY_F14 = 0x00,
		LLE_KEY_F15 = 0x00,
		LLE_KEY_F16 = 0x00,
		LLE_KEY_F17 = 0x00,
		LLE_KEY_F18 = 0x00,
		LLE_KEY_F19 = 0x00,
		LLE_KEY_F20 = 0x00,
		LLE_KEY_F21 = 0x00,
		LLE_KEY_F22 = 0x00,
		LLE_KEY_F23 = 0x00,
		LLE_KEY_F24 = 0x00,
		LLE_KEY_LEFT_ALT = 0x00,
		LLE_KEY_LEFT_CONTROL = 0x00,
		LLE_KEY_LEFT_SHIFT = 0x00,
		LLE_KEY_LEFT_SUPER = 0x00,
		LLE_KEY_PRINT_SCREEN = 0x00,
		LLE_KEY_RIGHT_ALT = 0x00,
		LLE_KEY_RIGHT_CONTROL = 0x00,
		LLE_KEY_RIGHT_SHIFT = 0x00,
		LLE_KEY_RIGHT_SUPER = 0x00,
		LLE_KEY_DOWN = 0x00,
		LLE_KEY_LEFT = 0x00,
		LLE_KEY_RIGHT = 0x00,
		LLE_KEY_UP = 0x00,
		LLE_KEY_KP_0 = 0x00,
		LLE_KEY_KP_1 = 0x00,
		LLE_KEY_KP_2 = 0x00,
		LLE_KEY_KP_3 = 0x00,
		LLE_KEY_KP_4 = 0x00,
		LLE_KEY_KP_5 = 0x00,
		LLE_KEY_KP_6 = 0x00,
		LLE_KEY_KP_7 = 0x00,
		LLE_KEY_KP_8 = 0x00,
		LLE_KEY_KP_9 = 0x00,
		LLE_KEY_KP_ADD = 0x00,
		LLE_KEY_KP_DECIMAL = 0x00,
		LLE_KEY_KP_DIVIDE = 0x00,
		LLE_KEY_KP_ENTER = 0x00,
		LLE_KEY_KP_EQUAL = 0x00,
		LLE_KEY_KP_MULTIPLY = 0x00,
		LLE_KEY_KP_SUBTRACT = 0x00
	};
#endif
	enum MouseButtons
	{
		LLE_BUTTON_RIGHT = 0,
		LLE_BUTTON_LEFT = 1,
		LLE_BUTTON_MIDDLE = 2
	};
}

namespace LunaLuxEngine::window_api
{
	class CrossWindow
	{
	private:
		LLEbool keys[256] = {};

		LLEbool M_buttons[3] = {};
#ifdef WIN32
	private:
		HWND hwnd{};

		HINSTANCE Inst{};

	public:
		inline HWND getWindow()
		{
			return hwnd;
		};

		LPCSTR class_name = (LPCSTR)"LunaLuxEngine_WindowClass";

		bool in_win = true;
	public:
		inline void mouseHandler(UINT Msg, WPARAM wParam, LPARAM lParam)
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
				{
					CWin->M_posx = ((DWORD_PTR)(lParam)) & 0xffff;
					CWin->M_posy = (((DWORD_PTR)(lParam)) >> 16) & 0xffff;
				}
				break;

			case WM_RBUTTONDOWN:
				CWin->setButton(0, 1);
				break;

			case WM_RBUTTONUP:
				CWin->setButton(0, 0);
				break;

			case WM_LBUTTONDOWN:
				CWin->setButton(1, 1);
				break;

			case WM_LBUTTONUP:
				CWin->setButton(1, 0);
				break;

			case WM_MBUTTONDOWN:
				CWin->setButton(2, 1);
				break;

			case WM_MBUTTONUP:
				CWin->setButton(2, 0);
				break;

			default:
				break;
			}
		};

		inline void keyboardHandler(UINT Msg, WPARAM wParam, LPARAM lParam)
		{
			switch (Msg)
			{
			case WM_KEYDOWN:
				CWin->setKey(wParam, 1);
				break;

			case WM_KEYUP:
				CWin->setKey(wParam, 0);
				break;

			default:
				break;
			}
		};

		inline void commonHandler(UINT Msg, WPARAM wParam, LPARAM lParam)
		{
			switch (Msg)
			{
			case WM_CLOSE:
				WIN_SHOULD_CLOSE = LLEtrue;
				break;

			case WM_SIZE:
				CWin->fireResizeCallback(MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y);
				break;

			default:
				break;
			}
		};

#endif
#ifdef  __linux__
	private:
		int                     att[5] = { 4, 12, 24, 5, 0L };

		Display* dpy{};

		Window                  root{};

		Window                  win{};

		XSetWindowAttributes    swa{};

		Colormap                cmap{};

		XVisualInfo* vi{};

		XEvent                  xev{};
	public:
		inline Display* getWindowL()
		{
			return dpy;
		};

		inline Window getWindowL_()
		{
			return win;
		};

		inline XVisualInfo* getWindowV()
		{
			return vi;
		};
#endif
	protected:
		int8* Title = (int8*)"temp";

		int16 width = 800, height = 600;

		void(*resizeCallback)(int32, int32) = nullptr;
	public:
		int16 M_posx = 0, M_posy = 0;

		LLEbool WIN_SHOULD_CLOSE = LLEfalse;

		inline LLEbool isKeyDown(int code)
		{
			if (keys[code] != 0) return LLEtrue
			else return LLEfalse
		};

		inline LLEbool isMouseButtonDown(int buttons)
		{
			if (M_buttons[buttons] != 0) return LLEtrue
			else return LLEfalse
		};

		inline int16 getPosX()
		{
			return M_posx;
		};

		inline int16 getPosY()
		{
			return M_posy;
		};

		inline void setKey(int32 code, LLEbool state)
		{
			keys[code] = state;
		};

		inline void setButton(int32 code, LLEbool state)
		{
			M_buttons[code] = state;
		};

		void createWindow();

		inline void setTitle(int8* in_title)
		{
			Title = in_title;
		};
		inline void setSize(int16 in_width, int in_height)
		{
			width = in_width;
			height = in_height;
			fireResizeCallback(in_width, in_height);
		};
		inline int8* getTitle()
		{
			return Title;
		};
		inline LLEbool shouldClose()
		{
			return  WIN_SHOULD_CLOSE;
		};
		void updateWindow();
		void destoryWindow();

		inline float getWindowW()
		{
			return width;
		};
		inline float getWindowH()
		{
			return height;
		};

		inline void CrossWindow::fireResizeCallback(int32 in_width, int32 in_height)
		{
			if (resizeCallback != nullptr) resizeCallback(in_width, in_height);
		};

		inline void setResizeCallback(void(*callback)(int32, int32))
		{
			resizeCallback = callback;
		};
		void fireResizeCallback(int32, int32);

		inline static CrossWindow* get()
		{
			static auto* window_ = new CrossWindow();
			return window_;
		};
	};
}