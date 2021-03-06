//
// Created by luket on 09/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include "StringUtils.h"
// TODO: write documentation
namespace LunaLux
{
std::string strCombine(const std::string& string_0,const std::string& string_1)
{
    return (string_0 + string_1);
}

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
        temp += ch;
    }
    res.emplace_back(temp);
    return std::move(res);
}
}