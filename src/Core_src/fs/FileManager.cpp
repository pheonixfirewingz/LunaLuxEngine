//
// Created by luket on 18/08/2020.
//

#include "FileManager.h"
#include "Windows/WindowsFileManager.h"

FileManager::FileManager()
{
#ifdef LLE_WINDOWS
    fileManager = new WindowsFileManager();
#endif
    LOG("TODO: finish writing files in file manager")
}

std::string FileManager::readFile(std::string path)
{
    return fileManager->readfile(path);
}

std::string FileManager::getAbsolutePath(std::string path)
{
    return fileManager->getAbsolutePath(path);
}
