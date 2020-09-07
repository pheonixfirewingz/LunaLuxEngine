//
// Created by digitech on 07/09/2020.
//

#include "LinuxFileManager.h"
#include <filesystem>
#include <istream>
#include <fstream>

LinuxFileManager::LinuxFileManager()
{
    current_binery_location = std::filesystem::current_path().string();
}

std::string LinuxFileManager::readfile(std::string inpath)
{
    std::string longpath = getAbsolutePath(inpath);
    if (!std::filesystem::exists(longpath.c_str()))
    { return "ERROR: FILE DOSE NOT EXISTS"; }
    std::ifstream file(longpath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        std::string string;
        file.seekg(0, std::ios::end);
        string.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        string.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        return string;
    }
    else
    { return "ERROR: COUNT NOT OPEN FILE"; }
}

void LinuxFileManager::writefile(std::string, std::string, bool)
{
    LOG("TODO: linux write files not implemented")
}

std::string LinuxFileManager::getAbsolutePath(std::string path)
{
    return current_binery_location + "/" + path;
}
