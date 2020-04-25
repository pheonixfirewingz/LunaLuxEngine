#ifdef WIN32
#include <Windows.h>
#pragma comment(lib,"Winmm.lib")
#endif
#include "EnginePanic.h"
#include "../window/Window.h"

void LunaLuxEngine::EnginePanic::panic(std::string msg)
{
    std::string temp;
    temp += "\\( '0' )/ Engine Panic!  \\( '0' )/: ";
    temp += msg.c_str();
	printf("%s\n", temp.c_str());
#ifdef WIN32
    PlaySound("Windows Background", NULL, SND_SYNC);
#endif
    CWin.updateTitle((int8*)temp.c_str());
	while (!CWin.getNativeWindow()->getInputController()->isKeyDown(window_api::LLE_KEY_SPACE) || !CWin.shouldClose()) CWin.updateWindow();
	std::exit(-1);
}
