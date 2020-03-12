#ifndef LUNALUXENGINE_CROSSWINDOW_H
#define LUNALUXENGINE_CROSSWINDOW_H
#include <LLESDK/types.h>
#include "IWindow.h"
#include "Win32Window.h"
#ifdef __linux__
#include <cstring>
#include <X11/X.h>
#include <X11/Xlib.h>
#endif
#define CWin LunaLuxEngine::window_api::CrossWindow::get()

namespace LunaLuxEngine::window_api
{
	enum class WindowType
	{
		Win32Window = 0,
	};
	class CrossWindow
	{
		IWindow* window;
#ifdef UWP
#ifdef WIN32
	private:

	public:
		HWND getWin32Window() { return FindWindowA((LPCSTR)"LunaLuxEngine_WindowClass", (LPCSTR)window->getTitle()); };
#endif
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
	public:
		CrossWindow(CrossWindow const&) = delete;
		void operator=(CrossWindow const&) = delete;
		CrossWindow() {};
		~CrossWindow() {};
		void setWindowType(WindowType type);
		void createWindow() { window->createWindow(); };
		void updateWindow();
		void destoryWindow() { window->destoryWindow(); };
		void setShouldClose(LLEbool close) { window->setShouldClose(close); };
		void setTitle(int8* title) { window->setTitle(title); };
		void setSize(int32 width, int32 height) { window->setSize(width, height); };
		LLEbool shouldClose() { return window->shouldClose(); };

		inline IWindow* getNativeWindow()
		{
			return window;
		};

		inline static CrossWindow& get()
		{
			static CrossWindow window_;
			return window_;
		};
	};
}
#endif // !LUNALUXENGINE_CROSSWINDOW_H