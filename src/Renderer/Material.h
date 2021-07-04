#pragma once
//
// Created by luket on 01/07/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
// TODO: write documentation
#include <cstdint>
namespace LunaLux
{
struct Material
{
    [[maybe_unused]] float diffuse[3]{0.0,0.0,0.0};
    [[maybe_unused]] float base_colour[3]{0.0,0.0,0.0};
    [[maybe_unused]] float luminance{1.0};
    [[maybe_unused]] int8_t roughness{0};
    [[maybe_unused]] uint16_t texture_id{0};
};
} // namespace LunaLux