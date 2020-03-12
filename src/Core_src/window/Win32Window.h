#ifndef LUNALUXENGINE_WIN32WINDOW_H
#define LUNALUXENGINE_WIN32WINDOW_H
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#include <windows.h>
#include <windowsx.h>
#endif
#include "IWindow.h"
namespace LunaLuxEngine::window_api
{
#ifdef WIN32
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
#else
	class Win32Window : public IWindow
	{
	public:
		void createWindow() override {};
		void destoryWindow() override {};
	};
#endif
}
#endif