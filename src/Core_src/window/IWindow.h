#ifndef LUNALUXENGINE_IWINDOW_H
#define LUNALUXENGINE_IWINDOW_H
#include <LLESDK/types.h>
#include "Input.h"
namespace LunaLuxEngine::window_api
{
	class IWindow
	{
	protected:
		int32 width = 800, height = 600;
		int8* Title = (int8*)"temp";
		void(*resizeCallback)(int32, int32) = nullptr;
		LLEbool WIN_SHOULD_CLOSE = LLEfalse;
	public:
		virtual void createWindow() = 0;
		virtual void updateWindow() = 0;
		virtual void updateTitle(int8*) = 0;
		virtual void destoryWindow() = 0;

		inline int32 getWindowW()
		{
			return width;
		};
		inline int32 getWindowH()
		{
			return height;
		};
		inline void setTitle(int8* in_title)
		{
			Title = in_title;
		};
		inline void setSize(int32 in_width, int32 in_height)
		{
			width = in_width;
			height = in_height;
			fireResizeCallback(in_width, in_height);
		};
		inline int8* getTitle()
		{
			return Title;
		};
		inline void setShouldClose(LLEbool close)
		{
			WIN_SHOULD_CLOSE = close;
		};
		inline LLEbool shouldClose()
		{
			return  WIN_SHOULD_CLOSE;
		};
		inline void fireResizeCallback(int32 in_width, int32 in_height)
		{
			if (resizeCallback != nullptr) resizeCallback(in_width, in_height);
		};
		inline void fireResizeCallback()
		{
			if (resizeCallback != nullptr) resizeCallback(width, height);
		};
		inline void setResizeCallback(void(*callback)(int32, int32))
		{
			resizeCallback = callback;
		};
		inline InputControls* getInputController()
		{
			static InputControls* input = new InputControls();
			return input;
		};
	};
}
#endif