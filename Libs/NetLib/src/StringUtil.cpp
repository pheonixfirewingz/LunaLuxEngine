#include "StringUtil.h"
//
// Created by luket on 20/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
// TODO: write documentation
namespace LunaLux::net
{
std::vector<std::string> split(const std::string &input, char delim)
{
    std::vector<std::string> res;
    std::string temp;
    for (auto ch : input)
    {
        if(ch == delim)
        {
            res.emplace_back(temp);
            temp.clear();
        }
        else temp += ch;
    }
    res.emplace_back(temp);
    return std::move(res);
}
}