//
// Created by luket on 18/08/2020.
//

#ifndef LUNALUXENGINE_WINDOWSFILEMANAGER_H
#define LUNALUXENGINE_WINDOWSFILEMANAGER_H

#include <LLESDK/types.h>
#include "../common/IFileManager.h"

namespace LunaLuxEngine
{

    class WindowsFileManager : public IFileManager
    {
    private:
        std::string current_binery_location;
    public:
#ifdef LLE_WINDOWS

        WindowsFileManager();

        std::string readfile(std::string string) override;

        void writefile(std::string,std::string,bool) override;

        std::string getAbsolutePath(std::string string) override;

#else
        WindowsFileManager() {};
        ~WindowsFileManager() {};
        std::string readfile(std::string string) override {return std::string("ERROR: OS IS NOT WINDOWS");};
        void writefile(std::string string) override { return std::string("ERROR: OS IS NOT WINDOWS");};
        std::string getAbsolutePath(std::string string) override {return std::string("ERROR: OS IS NOT WINDOWS");};
#endif
    };

}
#endif //LUNALUXENGINE_WINDOWSFILEMANAGER_H
