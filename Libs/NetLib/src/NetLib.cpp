//
// Created by luket on 05/04/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <Api/NetLib.h>
#include <memory>
#include <atomic>
#if __has_include(<sys/socket.h>)
#    include <linux/LinuxNetManager.hpp>
std::unique_ptr<LunaLux::net::LinuxNetManager> manager;
#endif
namespace LunaLux::net
{
NetworkType current_type_state {NetworkType::SERVER};
std::atomic_bool is_conection_open{false};

NetResult netInit() noexcept
{
#if __has_include(<sys/socket.h>)
    manager = std::make_unique<LinuxNetManager>();
#endif
    return NetResult::SUCSESS;
}

void setNetworkType(NetworkType type) noexcept
{
    if(current_type_state == type) return;
    if(is_conection_open) disconnect();

    current_type_state = type;
}

NetResult connect(const std::string &ip) noexcept
{
    is_conection_open = true;
    switch (current_type_state)
    {
    case NetworkType::CLIENT:
        return static_cast<NetResult>(manager->createClientConnection(ip));
    case NetworkType::SERVER:
        return static_cast<NetResult>(manager->createServerConnection(ip));
    }
}

void *receive()
{
    if(!is_conection_open) throw std::runtime_error("LunaLuxNetLib: tried to read data from a non existent connection");
    switch (current_type_state)
    {
    case NetworkType::CLIENT:
        return nullptr;
    case NetworkType::SERVER:
        return nullptr;
    }
}

NetResult send(void *data, size_t byte_size) noexcept
{
    return NetResult::SUCSESS;
}

NetResult disconnect() noexcept
{
    is_conection_open = false;
    switch (current_type_state)
    {
    case NetworkType::CLIENT:
        return static_cast<NetResult>(manager->DestroyClientConnection());
    case NetworkType::SERVER:
        return static_cast<NetResult>(manager->DestroyServerConnection());
    }
}

void terminate() noexcept
{
    (void)manager.release();
}
}