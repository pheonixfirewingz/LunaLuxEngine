#include <cstdio>
#include <cstdlib>
#include "Window.h"
#include <exception>
namespace LunaLuxEngine::window_api
{
	void CrossWindow::setWindowType(WindowType type)
	{
		if (type == WindowType::Win32Window) window = new Win32Window();
		else if (type == WindowType::X11Window) window = new X11Window();
	}
}