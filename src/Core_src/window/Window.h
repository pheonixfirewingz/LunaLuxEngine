#ifndef LUNALUXENGINE_CROSSWINDOW_H
#define LUNALUXENGINE_CROSSWINDOW_H
#include <LLESDK/types.h>
#include "IWindow.h"
#include "Win32Window.h"
#include "X11Window.h"
#define CWin LunaLuxEngine::window_api::CrossWindow::get()

namespace LunaLuxEngine::window_api
{
	enum class WindowType
	{
		Win32Window = 0,
		X11Window = 1,
	};
	class CrossWindow
	{
        IWindow *window;
#ifdef WIN32
	public:
		HWND getWin32Window() { return FindWindowA((LPCSTR)"LunaLuxEngine_WindowClass", (LPCSTR)window->getTitle()); };
#endif
#ifdef  temp
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
		void updateTitle(int8* title_) {window->updateTitle(title_);};
		void updateWindow() {window->updateWindow();};
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