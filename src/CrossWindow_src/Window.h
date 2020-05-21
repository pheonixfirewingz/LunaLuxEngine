#ifndef LUNALUXENGINE_CROSSWINDOW_H
#define LUNALUXENGINE_CROSSWINDOW_H
#include <LLESDK/types.h>
#include "IWindow.h"
#include "Win32Window.h"
#include "X11Window.h"
#define CWin LunaLuxEngine::window_api::CrossWindow::get()
/* MAIN WINDOW CLASS
 *-----------------------------------------------
 * this is the main window api interface this is the class that is
 * used for the abstraction of diffrent operating systems.
 *-----------------------------------------------
 */
namespace LunaLuxEngine::window_api
{
	//this is used to set the window api type.
	enum class WindowType
	{
		Win32Window = 0,
		X11Window = 1,
	};
	class CrossWindow
	{
		// IWindow class
		// this is the main window class it is extended by Win32Window and X11Window
		IWindow* window;
#ifdef WIN32
	public:
		// this is to help create the win32 OpenGL Context
		HWND getWin32Window() { return FindWindowA((LPCSTR)"LunaLuxEngine_WindowClass", (LPCSTR)window->getTitle()); };
		HINSTANCE getWin32WindowInst() { return GetModuleHandle((LPCSTR)"LunaLuxEngine_WindowClass"); };
#endif
#ifdef  temp
	public:
		/* this is broken
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
		};*/
#endif
	public:
		//this is to make the class as a singleton
		CrossWindow(CrossWindow const&) = delete;
		void operator=(CrossWindow const&) = delete;
		// empty constructor
		CrossWindow() {};
		// empty destructor
		~CrossWindow() {};
		//this is the only method of the window api that is not platform dependant
		void setWindowType(WindowType type);
		//this calls the the window creation from the extended class.
		void createWindow() { window->createWindow(); };
		//TODO: this only works on windows this needs adding to linux X11 extended class
		//this calls the window title change
		void updateTitle(int8* title_) { window->updateTitle(title_); };
		//this calls the extended classes update virtual function
		void updateWindow() { window->updateWindow(); };
		//this is used to destroy the platforms window
		void destoryWindow() { window->destoryWindow(); };
		//this is used to override the operating system call if is only really needed for shutdown
		void setShouldClose(LLEbool close) { window->setShouldClose(close); };
		//-------------------------------------------------------------------------------------
		//this is to set the window title before booting the window
		void setTitle(int8* title) { window->setTitle(title); };
		//this is to set the window size before window boot
		void setSize(int32 width, int32 height) { window->setSize(width, height); };
		//this is used to ask the operating system if the window of the game has closed
		LLEbool shouldClose() { return window->shouldClose(); };
		// this gets the non extended version of the window this is used for the cross platforms functions
		inline IWindow* getNativeWindow()
		{
			return window;
		};
		//this is used to get the window of the api
		inline static CrossWindow& get()
		{
			static CrossWindow window_;
			return window_;
		};
	};
}
#endif // !LUNALUXENGINE_CROSSWINDOW_H