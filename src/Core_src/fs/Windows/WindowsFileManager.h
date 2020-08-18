//
// Created by luket on 18/08/2020.
//

#ifndef LUNALUXENGINE_WINDOWSFILEMANAGER_H
#define LUNALUXENGINE_WINDOWSFILEMANAGER_H
#include <LLESDK/types.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "../common/IFileManager.h"

class WindowsFileManager : public IFileManager
{
private:
    std::string current_binery_location = std::filesystem::current_path().string();
public:
#ifdef LLE_WINDOWS
    std::string readfile(std::string string) override;
    void writefile(std::string string) override;

    std::string getAbsolutePath(std::string string) override;

#else
    WindowsFileManager() {};
    ~WindowsFileManager() {};
    std::string readfile(std::string string) override {};
    void writefile(std::string string) override {};
    std::string getAbsolutePath(std::string string) override {};
#endif
};


#endif //LUNALUXENGINE_WINDOWSFILEMANAGER_H
