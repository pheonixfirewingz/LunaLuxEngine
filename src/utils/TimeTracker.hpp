#pragma once
//
// Created by luket on 09/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include <utils/EngineDefines.h>
#include <LunaLux/WindowLib.h>
// TODO: write documentation
namespace LunaLux
{
class TimeTracker
{
    uint64_t start_time;
    std::string name;
  public:
    explicit TimeTracker(std::string in_name) : name(std::move(in_name))
    {
        start_time = getTime();
    }

    ~TimeTracker()
    {
        LOG("TimeTracker{%s} - took %lli ms\n",name.c_str(),nsToMs((getTime() - start_time)))
    }
};
} // namespace LunaLux