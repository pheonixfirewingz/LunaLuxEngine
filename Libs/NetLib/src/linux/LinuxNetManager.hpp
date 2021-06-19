#pragma once
//
// Created by luket on 19/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <Definds.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
namespace LunaLux::net
{
class LinuxNetManager
{
  public:
    Result createClientConnection(std::string ip)
    {
            return Result::SUCSESS;
    }

    Result createServerConnection(std::string ip)
    {
        return Result::SUCSESS;
    }

    Result DestroyClientConnection()
    {
        return Result::SUCSESS;
    }

    Result DestroyServerConnection()
    {
        return Result::SUCSESS;
    }
};
}