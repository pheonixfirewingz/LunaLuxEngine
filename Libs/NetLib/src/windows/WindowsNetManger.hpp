#pragma once
//
// Created by luket on 29/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
namespace LunaLux::net
{
class WindowsNetManager
{
    bool client{false};
  public:
    [[nodiscard]] NetResult createClientConnection(const std::string& ip) noexcept
    {
        client = true;

        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult createServerConnection(const std::string& ip) noexcept
    {
        client = false;

        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult receive(void** data,size_t byte_size) const
    {
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult sendPackage(void* data,size_t byte_size) const noexcept
    {
        return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult waitForClientConnection() const noexcept
    {
       return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult accept_client() noexcept
    {
       return NetResult::SUCSESS;
    }

    [[nodiscard]] NetResult destroyConnection() const noexcept
    {
        return NetResult::SUCSESS;
    }
};
} // namespace LunaLux::net