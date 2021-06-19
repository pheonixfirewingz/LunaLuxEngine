#pragma once
//
// Created by luket on 05/04/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#if __has_include(<windows.h>)
#ifndef LIB_APP
#    define LLNL_EXPORT __declspec(dllexport)
#else
#    define LLNL_EXPORT __declspec(dllimport)
#endif
#else
#ifndef LIB_APP
#ifndef STATIC_LIB
#define LLNL_EXPORT __attribute__((visibility("default")))
#else
#define LLNL_EXPORT
#endif
#endif
#endif
#include <string>
//TODO: write documentation
namespace LunaLux::net
{
enum class NetResult
{
    SUCSESS = 0,
};

enum class NetworkType
{
    CLIENT = 0,
    SERVER = 1,
};

LLNL_EXPORT NetResult netInit() noexcept;
LLNL_EXPORT void setNetworkType(NetworkType type) noexcept;
LLNL_EXPORT NetResult connect(const std::string& ip) noexcept;
LLNL_EXPORT void* receive();
LLNL_EXPORT NetResult send(void* data,size_t byte_size) noexcept;
LLNL_EXPORT NetResult disconnect() noexcept;
LLNL_EXPORT void terminate() noexcept;

} // namespace LunaLux
