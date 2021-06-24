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
//this is used to tell the library user if the network function failed with out using exceptions
enum class NetResult
{
    SUCSESS = 0,
    ERROR = 1,
};

//this is the library connection states
enum class NetworkType
{
    CLIENT = 0,
    SERVER = 1,
};

enum class Protocol
{
    TCP = 0,
    UDP = 1,
};
//this is the common network functions
//this is called to set up the internal network manager to handle operating system pacific network apis
LLNL_EXPORT NetResult netInit() noexcept;
//this is used to set the library internal state to tell the lib to work as ether a client or server
LLNL_EXPORT void setNetworkType(NetworkType type) noexcept;

LLNL_EXPORT void setProtocol(Protocol protocol) noexcept;
//=====================================================================================================================
//                                  names explain what they do
LLNL_EXPORT NetResult connect(const std::string& ip) noexcept;
LLNL_EXPORT NetResult receive(void** data,size_t byte_size);
LLNL_EXPORT NetResult send(void *data, size_t byte_size) noexcept;
LLNL_EXPORT NetResult disconnect() noexcept;
//=====================================================================================================================
LLNL_EXPORT void terminate() noexcept;
//this is unique server pacific function
LLNL_EXPORT NetResult waitForClientConnection() noexcept;
} // namespace LunaLux
