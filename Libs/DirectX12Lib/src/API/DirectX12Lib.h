#pragma once
//
// Created by luket on 05/04/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#ifndef LIB_APP
#    define LLVL_EXPORT __declspec(dllexport)
#else
#    define LLVL_EXPORT __declspec(dllimport)
#endif
#include <windows.h>
#include <tuple>
//TODO: write documentation
namespace LunaLux
{
// common functions
LLVL_EXPORT void directx12Init(HWND native_handle, const std::tuple<int, int> &size);
LLVL_EXPORT void directx12CleanUp() noexcept;

} // namespace LunaLux