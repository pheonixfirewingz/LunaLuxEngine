//
// Created by luket on 18/08/2020.
//

#include "FileManager.h"
#include "Windows/WindowsFileManager.h"
#include <string>
#include <sstream>
#include <iterator>
#include <utility>

FileManager::FileManager()
{
#ifdef LLE_WINDOWS
    fileManager = new WindowsFileManager();
#endif
    //"TODO: finish writing files in file manager"
}

std::string FileManager::readFile(std::string path)
{
    return fileManager->readfile(std::move(path));
}

std::string FileManager::getAbsolutePath(std::string path)
{
    return fileManager->getAbsolutePath(std::move(path));
}

obj_data FileManager::loadObj(std::string path)
{
    auto *mesh = new obj_data();
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> textureCoord;
        std::vector<std::string> s_vertices;
        std::vector<std::string> s_normals;
        std::vector<std::string> s_textureCoord;
        {
            std::vector<int> vertices_indices;
            std::vector<int> normal_indices;
            std::vector<int> textureCoord_indices;

            {
                std::vector<std::string> v_lines;
                std::vector<std::string> n_lines;
                std::vector<std::string> t_lines;
                std::vector<std::string> f_lines;
                {
                    std::vector<std::string> line = split(fileManager->readfile(std::move(path)), '\n');
                    for (int x = 0; x <= line.size() - 1; x++)
                    {
                        std::string data = line[x];
                        if (data.starts_with('v'))
                        {
                            if (data.starts_with("vt"))
                            { t_lines.push_back(data); }
                            else if (data.starts_with("vn"))
                            { n_lines.push_back(data); }
                            else
                            { v_lines.push_back(data); }
                        }
                        else if (data.starts_with('f'))
                        { f_lines.push_back(data); }
                    }
                }
                for (int x = 0; x <= v_lines.size() - 1; x++) s_vertices.push_back(split(v_lines[x], 'v')[1]);

                for (int x = 0; x <= t_lines.size() - 1; x++) s_textureCoord.push_back(split(t_lines[x], 't')[1]);

                for (int x = 0; x <= n_lines.size() - 1; x++) s_normals.push_back(split(n_lines[x], 'n')[1]);

                for (int x = 0; x <= f_lines.size() - 1; x++)
                {
                    std::vector<std::string> temp_data1 = split(split(f_lines[x], 'f')[1], ' ');
                    for (int y = 1; y <= temp_data1.size() - 1; y++)
                    {
                        std::vector<std::string> temp_data2 = split(temp_data1[y], '/');
                        vertices_indices.push_back(std::stoi(temp_data2[0]));
                        normal_indices.push_back(std::stoi(temp_data2[1]));
                        textureCoord_indices.push_back(std::stoi(temp_data2[2]));
                    }
                }
            }
            mesh->v_indices = vertices_indices;
        }
        for (int x = 0; x <= s_vertices.size() - 1; x++)
        {
            std::vector<std::string> temp_data = split(s_vertices[x], ' ');
            std::remove(temp_data.begin(), temp_data.end(), "");
            temp_data.resize(3);
            glm::vec3 temp_vec;
            temp_vec.x = std::stof(temp_data[0]);
            temp_vec.y = std::stof(temp_data[1]);
            temp_vec.z = std::stof(temp_data[2]);
            vertices.push_back(temp_vec);
        }

        for (int x = 0; x <= s_textureCoord.size() - 1; x++)
        {
            std::vector<std::string> temp_data = split(s_textureCoord[x], ' ');
            std::remove(temp_data.begin(), temp_data.end(), "");
            temp_data.resize(2);
            glm::vec2 temp_vec;
            temp_vec.x = std::stof(temp_data[0]);
            temp_vec.y = std::stof(temp_data[1]);
            textureCoord.push_back(temp_vec);
        }

        for (int x = 0; x <= s_normals.size() - 1; x++)
        {
            std::vector<std::string> temp_data = split(s_normals[x], ' ');
            std::remove(temp_data.begin(), temp_data.end(), "");
            temp_data.resize(3);
            glm::vec3 temp_vec;
            temp_vec.x = std::stof(temp_data[0]);
            temp_vec.y = std::stof(temp_data[1]);
            temp_vec.z = std::stof(temp_data[2]);
            normals.push_back(temp_vec);
        }

        mesh->vertices = vertices;
        mesh->normals = normals;
        mesh->texcoords = textureCoord;
    }
    return *mesh;
}

std::vector<std::string> FileManager::split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}