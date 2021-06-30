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

#define CHECK(name, args)        \
    if (name args < 0)           \
    {                            \
        perror(#name);           \
        return NetResult::ERROR; \
    }

#define CHECK_WITH_RET(ret, name, args) \
    if ((ret = name args) < 0)          \
    {                                   \
        perror(#name);                  \
        return NetResult::ERROR;        \
    }

class LinuxNetManager
{
    int32_t m_socket = 0, m_client_socket = 0;
    sockaddr_in m_address{},m_client_address{};
    bool client{false};

  public:
    [[nodiscard]] NetResult createClientConnection(const std::string &ip) noexcept
    {
        client = true;
        auto splits = split(ip, ':');
        std::string ip_address = splits[0], port = splits[1];

        CHECK_WITH_RET(m_socket, socket, (AF_INET, SOCK_STREAM, 0))
        m_address.sin_family = AF_INET;
        m_address.sin_port = htons(std::stoi(port));

        CHECK(inet_pton,(AF_INET, "127.0.0.1", &m_address.sin_addr))
        CHECK(connect,(m_socket, reinterpret_cast<sockaddr *>(&m_address), sizeof(m_address)))
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult createServerConnection(const std::string &ip) noexcept
    {
        client = false;

        CHECK_WITH_RET(m_socket, socket, (AF_INET, SOCK_STREAM, 0))
        m_address.sin_family = AF_INET;
        m_address.sin_port = htons(std::stoi(split(ip, ':')[1]));
        m_address.sin_addr.s_addr = htonl(INADDR_ANY);

        CHECK(bind,(m_socket, reinterpret_cast<sockaddr *>(&m_address), sizeof(m_address)))
        return NetResult::SUCSESS;
    }

    [[nodiscard]] char *receive(size_t byte_size) const
    {
        char *buffer = new char[byte_size]{0};
        if (client)
        {
            size_t error = 0;
            if ((error = recv(m_socket, buffer, byte_size, 0)) < 0)
            {
                printf("LunaLuxNetLib: error - &ul", error);
                delete[] buffer;
                return nullptr;
            }
        }
        else
        {
            size_t error = 0;
            if ((error = recv(m_client_socket, buffer, 1024, 0)) < 0)
            {
                printf("LunaLuxNetLib: error - &ul", error);
                delete[] buffer;
                return nullptr;
            }
        }
        printf("LunaLuxNetLib: Debug - %s\n", buffer);
        return buffer;
    }

    [[nodiscard]] NetResult sendPackage(void *data, size_t byte_size) const noexcept
    {
        if (client)
        {
            CHECK(::send,(m_socket, data, byte_size, 0));
        }
        else
        {
            CHECK(::send,(m_client_socket, data, byte_size, 0));
        }
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult waitForClientConnection() const noexcept
    {
        CHECK(listen,(m_socket, 3))
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult accept_client() noexcept
    {
        //FIXME: accept: Bad address - WTF
        auto * size = reinterpret_cast<socklen_t *>(sizeof(sockaddr_in));
        CHECK_WITH_RET(m_client_socket,accept,(m_socket, reinterpret_cast<sockaddr *>(&m_client_address),size))
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult destroyConnection() const noexcept
    {
        CHECK(close,(m_socket))
        return NetResult::SUCSESS;
    }
};
} // namespace LunaLux::net