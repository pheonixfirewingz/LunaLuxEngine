//
// Created by digitech on 07/09/2020.
//

#ifndef LUNALUXENGINE_LINUXFILEMANAGER_H
#define LUNALUXENGINE_LINUXFILEMANAGER_H
#include <LLESDK/types.h>
#include "../common/IFileManager.h"

class LinuxFileManager: public IFileManager
{
private:
    std::string current_binery_location;
public:
    LinuxFileManager();

    std::string readfile(std::string string) override;

    void writefile(std::string,std::string,bool) override;

    std::string getAbsolutePath(std::string string) override;
};


#endif //LUNALUXENGINE_LINUXFILEMANAGER_H
