//
// Created by luket on 18/08/2020.
//

#ifndef LUNALUXENGINE_FILEMANAGER_H
#define LUNALUXENGINE_FILEMANAGER_H
#include <LLESDK/types.h>
#include "common/IFileManager.h"

class FileManager
{
private:
    IFileManager* fileManager;
public:
    FileManager();
    std::string readFile(std::string);
    std::string getAbsolutePath(std::string);

    static FileManager* get()
    {
        FileManager* manager = new FileManager();
        return manager;
    }
};


#endif //LUNALUXENGINE_FILEMANAGER_H
