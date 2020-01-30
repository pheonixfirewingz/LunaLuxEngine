#pragma once

#include <LunaLuxEngine/Common_Header.h>
#include <vector>

#ifdef  WIN32
#include <windows.h>
class IRender
{
public:
	void initRender(HWND);
	void prepRender();
	void fireRender();
	void destroyRender();
};
#else
class IRender
{
protected:
public:
	void initRender();
	void prepRender();
	void fireRender();
	void destroyRender();
};
#endif

