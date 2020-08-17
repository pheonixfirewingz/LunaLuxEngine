#ifndef LUNALUXENGINE_CROSSWINDOW_H
#define LUNALUXENGINE_CROSSWINDOW_H
#include <LLESDK/types.h>
#include <cstdlib>
#include "IWindow.h"
#include "Win32Window.h"
#include "X11Window.h"
#include "WindowPanic.h"

#define CWin LunaLuxEngine::window_api::CrossWindow::get()
/* MAIN WINDOW CLASS
 *-----------------------------------------------
 * this is the main window api interface this is the class that is
 * used for the abstraction of diffrent operating systems.
 *-----------------------------------------------
 */
namespace LunaLuxEngine::window_api
{

	class CrossWindow
	{
		// IWindow class
		// this is the main window class it is extended by Win32Window and X11Window
		IWindow* window;
		bool OpenGLMode{false};
	public:
		//this is to make the class as a singleton
		CrossWindow(CrossWindow const&) = delete;
		void operator=(CrossWindow const&) = delete;
		// empty constructor
		CrossWindow() {};
		// empty destructor
		~CrossWindow() {};

        //this sets up the window to be win32, x11, wayland(to be added) and cocoa(to be added)
		void giveWindowInfo(WindowInfo& windowInfo);
		//this calls the the window creation from the extended class.
		void createWindow() { window->createWindow(OpenGLMode); };
		//this calls the window title change
		void updateTitle(int8* title_) { window->updateTitle(title_); };
		//this calls the extended classes update virtual function
		void updateWindow() { window->updateWindow(OpenGLMode); };
		//this is used to destroy the platforms window
		void destoryWindow() { window->destoryWindow(OpenGLMode); };
		//this is used to override the operating system call if is only really needed for shutdown
		void setShouldClose(LLEbool close) { window->setShouldClose(close); };
		//this is used to ask the operating system if the window of the game has closed
		LLEbool shouldClose() { return window->shouldClose(); };
		//get's window info
		WindowInfo& getWindowInfo() { return window->info; }
		// this gets the non extended version of the window this is used for the cross platforms functions
		inline IWindow* getNativeWindow() { return window; };
		//this is used to get the window of the api
		inline static CrossWindow& get()
		{
			static CrossWindow window_;
			return window_;
		};
	};
}
#endif // !LUNALUXENGINE_CROSSWINDOW_H