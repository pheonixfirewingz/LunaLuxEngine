//
// Created by luket on 18/08/2020.
//

#ifndef LUNALUXENGINE_FILEMANAGER_H
#define LUNALUXENGINE_FILEMANAGER_H

#include <LLESDK/types.h>
#include <vector>
#include <GLM/glm.hpp>
#include "common/IFileManager.h"


struct obj_data
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
     std::vector<glm::vec2> texcoords;
    std::vector<int> v_indices;
};

class FileManager
{
private:
    IFileManager *fileManager;
public:
    FileManager();

    static std::vector<std::string> split(const std::string &, char);

    std::string readFile(std::string);

    std::string readShaderFile(std::string,bool);

    std::string getAbsolutePath(std::string);

    obj_data loadObj(std::string);

    static FileManager *get()
    {
        FileManager *manager = new FileManager();
        return manager;
    }
};


#endif //LUNALUXENGINE_FILEMANAGER_H
