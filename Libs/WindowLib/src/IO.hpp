#pragma once
//
// Created by luket on 08/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
// TODO: write documentation
#include <bitset>
#include <cstdint>
#include <memory>
#include <mutex>
#include <tuple>
namespace LunaLux
{
class IO
{
  private:
    std::mutex lock;
    std::bitset<259> buttons;
    std::tuple<int64_t, int64_t> pos;
    uint64_t delta = 0.0f;

  public:
    IO() noexcept
    {
        buttons.reset();
    }

    void Reset()
    {
        // this is to stop undefined data reading or writing
        std::lock_guard<std::mutex> lockGuard(lock);
        buttons.reset();
    }

    void setButton(uint16_t button_position, bool button)
    {
        // this is to stop undefined data reading or writing
        std::lock_guard<std::mutex> lockGuard(lock);
        buttons.set(button_position, button);
    }

    bool isButtonDown(uint16_t keycode)
    {
        // this is to stop undefined data reading or writing
        std::lock_guard<std::mutex> lockGuard(lock);
        return buttons.test(keycode);
    }

    void setPosition(std::tuple<int64_t, int64_t> pos_in)
    {
        // this is to stop undefined data reading or writing
        std::lock_guard<std::mutex> lockGuard(lock);
        pos = std::move(pos_in);
    }

    std::tuple<int64_t, int64_t> getPosition()
    {
        // this is to stop undefined data reading or writing
        std::lock_guard<std::mutex> lockGuard(lock);
        return pos;
    }

    void setWheelDelta(uint64_t data)
    {
        // this is to stop undefined data reading or writing
        std::lock_guard<std::mutex> lockGuard(lock);
        delta = data;
    }

    uint64_t getWheelDelta()
    {
        // this is to stop undefined data reading or writing
        std::lock_guard<std::mutex> lockGuard(lock);
        return delta;
    }
};
} // namespace LunaLux
