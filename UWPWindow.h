#ifndef LUNALUXENGINE_WIN32WINDOW_H
#define LUNALUXENGINE_WIN32WINDOW_H
#include <LLESDK/types.h>
#include "IWindow.h"
namespace LunaLuxEngine::window_api
{

	class Win32Window : public IWindow
	{
	private:
		LPCSTR class_name = (LPCSTR)"LunaLuxEngine_WindowClass";
		HINSTANCE Inst{};
		HWND hwnd{};
	public:
		void createWindow() override;
		void destoryWindow() override;
	};
}
#endif