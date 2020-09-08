//
// Created by luket on 18/08/2020.
//

#include "WindowsFileManager.h"
#include "../FileManager.h"
#include "../../common/EnginePanic.h"

#ifdef LLE_WINDOWS
#include <windows.h>
#include <filesystem>

LunaLuxEngine::WindowsFileManager::WindowsFileManager()
{
    current_binery_location = std::filesystem::current_path().string();
}

std::string LunaLuxEngine::WindowsFileManager::readfile(std::string inpath)
{
    std::string temp_string = std::string(current_binery_location + "\\" + inpath);
    std::wstring temp_wide_string = std::wstring(temp_string.begin(), temp_string.end());

    HANDLE hFile = CreateFileW(temp_wide_string.c_str(), GENERIC_READ, FILE_SHARE_READ, 0,OPEN_EXISTING,
                                                                                        0, 0);

    if(hFile == INVALID_HANDLE_VALUE) return "ERROR: COULD NOT OPEN FILE CHECK 1";

    LARGE_INTEGER temp = {0};
    if( FALSE == GetFileSizeEx(hFile, &temp)) return "ERROR: COULD NOT OPEN FILE CHECK 2";

    DWORD  dwBytesRead = 0;
    DWORD dwBytesToRead = temp.QuadPart;
    char *array{ new char[temp.QuadPart - 1]{} };

    if( FALSE == ReadFile(hFile, array, dwBytesToRead, &dwBytesRead,NULL) ) return "ERROR: COULD NOT OPEN FILE CHECK 3";

    std::string data = std::string(array);
    std::string rut_data;
    //if not done string have non text characters quote "artifacts"
    for(int x = 0; x <= data.size() - 1;x++) if(FileManager::validTextCharatersForEngine(data[x])) rut_data += data[x];

    CloseHandle(hFile);
    return rut_data;
}

void LunaLuxEngine::WindowsFileManager::writefile(std::string path,std::string data_to_file,bool override)
{
    std::string temp_string = std::string(current_binery_location + "\\" + path);
    std::wstring temp_wide_string = std::wstring(temp_string.begin(), temp_string.end());

    HANDLE hFile = CreateFileW(temp_wide_string.c_str(), GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING,
                               0, 0);

    if (hFile == INVALID_HANDLE_VALUE) EnginePanic::get()->panic("WRITE ERROR: COULD NOT OPEN FILE");

    DWORD dwBytesWrite = 0;
    std::string dataWrite = data_to_file;
    DWORD dwBytesToWrite;

    if(override)
    {
        LARGE_INTEGER temp = {0};
        if (FALSE == GetFileSizeEx(hFile, &temp))
        {
            CloseHandle(hFile);
            EnginePanic::get()->panic("WRITE ERROR: COULD NOT GET FILE SIZE");
        }

        for (LARGE_INTEGER x = {0}; x.QuadPart <= temp.QuadPart - 1; x.QuadPart++) dataWrite += '~';

        dwBytesToWrite = strlen(dataWrite.c_str());
    }
    else dwBytesToWrite = strlen(data_to_file.c_str());

    if( FALSE == WriteFile(hFile, dataWrite.c_str(), dwBytesToWrite, &dwBytesWrite,NULL) )
    {
        CloseHandle(hFile);
        EnginePanic::get()->panic("WRITE ERROR: COULD NOT WRITE FILE");
    }
    CloseHandle(hFile);
}

std::string LunaLuxEngine::WindowsFileManager::getAbsolutePath(std::string path)
{
    return current_binery_location + "/" + path;
}

#endif