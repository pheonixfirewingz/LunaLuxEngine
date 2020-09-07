//
// Created by luket on 17/08/2020.
//

#include "WindowPanic.h"

[[noreturn]] void LunaLuxEngine::window_api::WindowPanic::panic(std::string msg)
{
    std::string temp;
    temp += "CrossWindow Fatal Error!: ";
    temp += msg.c_str();
    LOG(temp.c_str());
    for (;;);
}