#ifndef LUNALUXENGINE_IWINDOW_H
#define LUNALUXENGINE_IWINDOW_H
#include <LLESDK/types.h>
#include "Input.h"
// BASE CLASS FOR THE CROSS PLATFORM API
namespace LunaLuxEngine::window_api
{
    //this is used to set the window api type.
    enum class WindowType
    {
        Win32Window = 0,
        X11Window = 1,
        CocoaWindow = 2,
    };

    struct WindowInfo
    {
        WindowType windowType;
        bool HaveWindowCreateOpenGLContext;
        int8* title;
        int16 width,height;
    };

	// Base window class 
	class IWindow
	{
	protected:
		int32 width = 800, height = 600;
		int8* Title = (int8*)"temp";
		void(*resizeCallback)(int32, int32) = nullptr;
		LLEbool WIN_SHOULD_CLOSE = LLEfalse;
        //this is used to help resize the graphics apis render buffer size
        //this fires the window resize callback with custom width and height
        inline void fireResizeCallback(int32 in_width, int32 in_height)
        {
            if (resizeCallback != nullptr) resizeCallback(in_width, in_height);
        };
        //this fires the window resize callback
        inline void fireResizeCallback()
        {
            if (resizeCallback != nullptr) resizeCallback(width, height);
        };
	public:
        //this is the varables for storing window data
        WindowInfo info;
		//they are overriden by the extended classes for the operating system APIS. 
		virtual void createWindow(bool) = 0;
		virtual void updateWindow(bool) = 0;
		virtual void updateTitle(int8*) = 0;
		virtual void destoryWindow(bool) = 0;
		//this gets the window width
		inline int32 getWindowW()
		{
			return width;
		};
		//this gets the window height
		inline int32 getWindowH()
		{
			return height;
		};
		//this is to set the pre boot window title
		inline void setTitle(int8* in_title)
		{
			Title = in_title;
		};
		//this is used to set the resize data and fire callback
		inline void setSize(int32 in_width, int32 in_height)
		{
			width = in_width;
			height = in_height;
			fireResizeCallback(in_width, in_height);
		};
		//this is to get the window title
		inline int8* getTitle()
		{
			return Title;
		};
		//this is to set the window title before booting the window
		inline void setShouldClose(LLEbool close)
		{
			WIN_SHOULD_CLOSE = close;
		};
		//this is used to ask the operating system if the window of the game has closed
		inline LLEbool shouldClose()
		{
			return  WIN_SHOULD_CLOSE;
		};
		//this is used to set the callback
		inline void setResizeCallback(void(*callback)(int32, int32))
		{
			resizeCallback = callback;
		};
		//this is used to get the window input
		inline InputControls* getInputController()
		{
			static InputControls* input = new InputControls();
			return input;
		};
	};
}
#endif