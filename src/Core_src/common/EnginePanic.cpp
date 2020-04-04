#include "EnginePanic.h"

void LunaLuxEngine::EnginePanic::panic(std::string msg)
{
	printf("%s%s\n", "\\( '0' )/ Engine Panic!  \\( '0' )/:\n\n", msg.c_str());
	while (true);
}
