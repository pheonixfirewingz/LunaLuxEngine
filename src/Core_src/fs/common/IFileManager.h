//
// Created by luket on 18/08/2020.
//

#ifndef LUNALUXENGINE_IFILEMANAGER_H
#define LUNALUXENGINE_IFILEMANAGER_H

#include <string>

class IFileManager
{
public:
    virtual std::string readfile(std::string) = 0;

    virtual void writefile(std::string) = 0;

    virtual std::string getAbsolutePath(std::string) = 0;
};

#endif //LUNALUXENGINE_IFILEMANAGER_H
