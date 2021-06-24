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
    int32_t m_socket = 0,m_client_socket = 0;
    sockaddr_in m_address{};
    bool client{false};
    NetResult createSocket() noexcept
    {
        if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) return NetResult::ERROR;
        return NetResult::SUCSESS;
    }
  public:
    [[nodiscard]] NetResult createClientConnection(const std::string& ip) noexcept
    {
        client = true;
        auto splits = split(ip,':');
        std::string ip_address = splits[0],port = splits[1];

        if(createSocket() == NetResult::ERROR) return NetResult::ERROR;

        m_address.sin_family = AF_INET;
        m_address.sin_port = htons(std::stoi(port));

        if(inet_pton(AF_INET, "127.0.0.1", &m_address.sin_addr)<=0) return  NetResult::ERROR;

        if (connect(m_socket, reinterpret_cast<sockaddr*>(&m_address), sizeof(m_address)) < 0) return NetResult::ERROR;

        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult createServerConnection(const std::string& ip) noexcept
    {
        client = false;
        auto splits = split(ip,':');
        std::string port = splits[1];

        if(createSocket() == NetResult::ERROR) return NetResult::ERROR;

        m_address.sin_family = AF_INET;
        m_address.sin_port = htons(std::stoi(port));
        m_address.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(m_socket,reinterpret_cast<sockaddr*>(&m_address), sizeof(m_address)) < 0)
        {
            printf("LunaLuxNetLib: SERVER - port not available\n");
            return NetResult::ERROR;
        }

        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult receive(void** data,size_t byte_size) const
    {
        *data = malloc(byte_size);
        if(client)
        {
            size_t error = 0;
            if ((error = recv(m_socket, *data, byte_size, 0)) < 0)
            {
                printf("LunaLuxNetLib: error - &ul",error);
                free(*data);
                return NetResult::ERROR;
            }
        }
        else
        {
            size_t error = 0;
            if ((error = recv(m_client_socket, *data, byte_size, 0)) < 0)
            {
                printf("LunaLuxNetLib: error - &ul",error);
                free(*data);
                return NetResult::ERROR;
            }
        }
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult sendPackage(void* data,size_t byte_size) const noexcept
    {
        if(client)
        {
            size_t error = 0;
            if ((error = ::send(m_socket, data, byte_size, 0)) < 0)
            {
                printf("LunaLuxNetLib: error - &ul",error);
                return NetResult::ERROR;
            }
        }
        else
        {
            size_t error = 0;
            if((error = ::send(m_client_socket, data, byte_size, 0)) < 0)
            {
                printf("LunaLuxNetLib: error - &ul",error);
                return NetResult::ERROR;
            }
        }
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult waitForClientConnection() const noexcept
    {
        if (listen(m_socket,3) < 0) return NetResult::ERROR;
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult accept_client() noexcept
    {
        if((m_client_socket = accept(m_socket, (sockaddr*)&m_address, reinterpret_cast<socklen_t *>(sizeof(m_address)))) < 0)  return NetResult::ERROR;
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult destroyConnection() const noexcept
    {
        if(close(m_socket) < 0) return NetResult::ERROR;

        return NetResult::SUCSESS;
    }
};
} // namespace LunaLux::net