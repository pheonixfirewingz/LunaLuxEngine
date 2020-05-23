#include "EnginePanic.h"
#include "../../CrossWindow_src/Window.h"

void LunaLuxEngine::EnginePanic::panic(std::string msg)
{
    std::string temp;
    temp += "\\( '0' )/ Engine Panic!  \\( '0' )/: ";
    temp += msg.c_str();
	printf("%s\n", temp.c_str());
    CWin.updateTitle((int8*)temp.c_str());
	while (!CWin.shouldClose()) CWin.updateWindow();
	std::exit(0);
}
