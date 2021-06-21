#pragma once
//
// Created by luket on 19/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <Definds.h>
#include <StringUtil.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
namespace LunaLux::net
{
class LinuxNetManager
{
    int32_t m_socket, new_socket;


    NetResult createSocket()
    {
        if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) return NetResult::ERROR;
        return NetResult::SUCSESS;
    }
  public:
    NetResult createClientConnection(const std::string& ip)
    {
        auto splits = split(ip,':');
        std::string ip_address = splits[0],port = splits[1];

        if(createSocket() == NetResult::ERROR) return NetResult::ERROR;

        return NetResult::SUCSESS;
    }

    NetResult createServerConnection(const std::string& ip)
    {
        if(createSocket() == NetResult::ERROR) return NetResult::ERROR;

        return NetResult::SUCSESS;
    }

    NetResult receive(void** data,size_t byte_size)
    {
        *data = malloc(byte_size);
        if (::recv(m_socket,*data,byte_size,0) != 0)
        {
            free(data);
            return NetResult::ERROR;
        }
        return NetResult::SUCSESS;
    }
    NetResult sendPackage(const void* data,size_t byte_size)
    {
        if(::send(m_socket,data,byte_size,0) == 0) return NetResult::ERROR;
        return NetResult::SUCSESS;
    }

    NetResult waitForClientConnection()
    {
        if (listen(m_socket,3) < 0)
            return NetResult::ERROR;
        return NetResult::SUCSESS;
    }

    NetResult DestroyClientConnection()
    {
        return NetResult::SUCSESS;
    }

    NetResult DestroyServerConnection()
    {
        return NetResult::SUCSESS;
    }
};
} // namespace LunaLux::net