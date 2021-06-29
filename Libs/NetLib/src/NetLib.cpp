//
// Created by luket on 05/04/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <Api/NetLib.h>
#include <atomic>
#include <memory>
#if __has_include(<sys/socket.h>)
#    include <linux/LinuxNetManager.hpp>
std::unique_ptr<LunaLux::net::LinuxNetManager> manager;
#endif
#if __has_include(<windows.h>)
#include <stdexcept>
#include <windows/WindowsNetManger.hpp>
std::unique_ptr<LunaLux::net::WindowsNetManager> manager;
#endif
namespace LunaLux::net
{
NetworkType current_type_state {NetworkType::SERVER};
Protocol current_protocol_state {Protocol::TCP};
std::atomic_bool is_conection_open{false};

NetResult netInit() noexcept
{
#if __has_include(<sys/socket.h>)
    manager = std::make_unique<LinuxNetManager>();
#endif
#if __has_include(<windows.h>)
    manager = std::make_unique<WindowsNetManager>();
#endif
    return NetResult::SUCSESS;
}

void setNetworkType(NetworkType type) noexcept
{
    if(current_type_state == type) return;

    if(is_conection_open) disconnect();

    current_type_state = type;
}

void setProtocol(Protocol protocol) noexcept
{
    if(protocol == current_protocol_state) return;

    if(is_conection_open) disconnect();

    current_protocol_state = protocol;
}

NetResult connect(const std::string &ip) noexcept
{
    if(is_conection_open) return NetResult::SUCSESS;

    is_conection_open = true;
    switch (current_type_state)
    {
    case NetworkType::CLIENT:
        return manager->createClientConnection(ip);
    case NetworkType::SERVER:
        return manager->createServerConnection(ip);
    default:
        return NetResult::ERROR;
    }
}

NetResult receive(void** data,size_t byte_size)
{
    if(!is_conection_open) throw std::runtime_error("LunaLuxNetLib: tried to read data from a non existent connection");

    return manager->receive(data,byte_size);
}

NetResult send(void *data, size_t byte_size) noexcept
{
    return manager->sendPackage(data,byte_size);
}

NetResult disconnect() noexcept
{
    if(!is_conection_open) return NetResult::SUCSESS;

    is_conection_open = false;
    return manager->destroyConnection();
}


NetResult waitForClientConnection() noexcept
{
    if(current_protocol_state == Protocol::UDP) return NetResult::SUCSESS;

    if(current_type_state == NetworkType::CLIENT || !is_conection_open)
    {
        printf("LunaLuxNetLib: you tried to use waitForClientConnection in client mode or connection is not open");
        return NetResult::ERROR;
    }

    if (manager->waitForClientConnection() != NetResult::SUCSESS) return NetResult::ERROR;

    return manager->accept_client();
}

void terminate() noexcept
{
    disconnect();
    (void)manager.release();
}
}