#pragma once
//
// Created by digitech on 01/07/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
// TODO: write documentation
#include <vector>
namespace LunaLux
{
template<class type>
class ClientSocketManager
{
    std::vector<type> socket_store;
  public:

    uint8_t add(type socket)
    {
        socket_store.push_back(socket);
    }

    type get(uint8_t id)
    {
        return std::ref(socket_store[id]);
    }

    void remove(uint8_t id)
    {
        socket_store.erase(socket_store.begin() + id);
    }
};
} // namespace LunaLux