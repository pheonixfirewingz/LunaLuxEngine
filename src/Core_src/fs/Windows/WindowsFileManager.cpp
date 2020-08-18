//
// Created by luket on 18/08/2020.
//

#include "WindowsFileManager.h"
#ifdef LLE_WINDOWS

std::string WindowsFileManager::readfile(std::string inpath)
{
    std::string longpath = current_binery_location + "/" + inpath;
    if(!std::filesystem::exists(longpath.c_str())) return "ERROR: FILE DOSE NOT EXISTS";
    std::ifstream file(longpath.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

    if (file.is_open())
    {
        std::string string;
        file.seekg(0, std::ios::end);
        string.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        string.assign((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

        return string;
    }
    else return "ERROR: COUNT NOT OPEN FILE";
}

void WindowsFileManager::writefile(std::string path)
{
    if(!std::filesystem::exists(path.c_str()))
    {
    }
}

std::string WindowsFileManager::getAbsolutePath(std::string path)
{
    return current_binery_location + "/" + path;
}

#endif