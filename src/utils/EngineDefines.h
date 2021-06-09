#pragma once
//
// Created by luket on 08/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
// TODO: write documentation
#include <utils/StringUtils.h>
namespace LunaLux
{
enum class EngineResult
{
    SUCSESS = 0,
    DIRECTX_TWELVE_ERROR = 1,
    VULKAN_ERROR = 2,
    ENGINE_ERROR = 3
};
#define nsToMs(x) (x / 100000000)

#define LOG(f,...) printf(strCombine("\nLunaLuxEngine: ",f).c_str(), ##__VA_ARGS__);

#define CHECK(x, s)                            \
    {                                          \
        EngineResult result = x;               \
        if (result != EngineResult::SUCSESS)   \
        {                                      \
            HandleError(result, s);            \
            return EngineResult::ENGINE_ERROR; \
        }                                      \
    }
} // namespace LunaLux