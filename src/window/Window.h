#pragma once
#include "../Common_Header.h"
#ifdef WIN32
/*
 * The following #defines disable a bunch of unused windows stuff
 * removing some or all of these defines it will increase build time.
 */
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
#define STRICT
#include <Windows.h>
#define IDI_ICON1 101
#endif
namespace LunaLuxEngine::window_api
{
class Window
{
#ifdef WIN32
private:
	HWND hwnd{};
	HINSTANCE Inst{};
	bool WIN_SHOULD_CLOSE = false;
	public:
	HWND getWindow();
#endif
protected:
	char* Title = (char*)"temp";
	int16 width = 800,  height = 600;
public:
	void createWindow();
	void setTitle(char*);
	bool shouldClose();
	void updateWindow();
	void destoryWindow();
};
}