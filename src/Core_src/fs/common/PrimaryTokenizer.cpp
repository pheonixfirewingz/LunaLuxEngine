//
// Created by luket on 19/08/2020.
//
#include "ShaderParce.h"
#include "../FileManager.h"
#include "../../common/EnginePanic.h"

std::vector<LunaLuxEngine::LLEShaderLanguage::TOCKEN> LunaLuxEngine::LLEShaderLanguage::parceFromFiletoTockens(std::string path,bool vertex)
{
    std::vector<TOCKEN> tockens;
    std::vector<std::string> file_tockens;
    {
        std::vector<std::string> file_lines;
        if(vertex) file_lines = FileManager::get()->split(FileManager::get()->readFile(path + ".llesv"), '\n');
        else       file_lines = FileManager::get()->split(FileManager::get()->readFile(path + ".llesf"), '\n');
        if (file_lines[0].starts_with("ERROR"))
        {
            if(vertex)LunaLuxEngine::EnginePanic::get()->panic(file_lines[0] + ": " + path +".llesv");
            else      LunaLuxEngine::EnginePanic::get()->panic(file_lines[0] + ": " + path +".llesf");
        }
        for (int x = 0; x <= file_lines.size() - 1; x++)
        {
            std::vector<std::string> temp_data = FileManager::get()->split(file_lines[x], ' ');
            for (int y = 0; y <= temp_data.size() - 1; y++)
            {
                file_tockens.push_back(temp_data[y]);
            }
        }
    }
    for(int x = 0; x <= file_tockens.size() - 1; x++)
    {
        std::string tocken_d = file_tockens[x];
        if (tocken_d.starts_with(";"))
        {
                TOCKEN sub_token;
                sub_token.tocken = LLES_TOCKENS::LEND;
                tockens.push_back(sub_token);
        }
        if(!tocken_d.compare("in"))
        {
            TOCKEN tocken;
            tocken.tocken = LLES_TOCKENS::IN;
            tocken.value = file_tockens[x + 1] + " " + file_tockens[x + 2];
            x += 2;
            tockens.push_back(tocken);
        }
        if(!tocken_d.compare("out"))
        {
            TOCKEN tocken;
            tocken.tocken = LLES_TOCKENS::OUT;
            tocken.value = file_tockens[x + 1] + " " + file_tockens[x + 2];
            x += 2;
            tockens.push_back(tocken);
        }
        if(!tocken_d.compare("unf"))
        {
            TOCKEN tocken;
            tocken.tocken = LLES_TOCKENS::UNF;
            tocken.value = file_tockens[x + 1] + " " + file_tockens[x + 2];
            x += 2;
            tockens.push_back(tocken);
        }
        try
        {
            parceVariablestoTockens(tocken_d, file_tockens, tockens, x);
        }
        catch (const std::exception& ex)
        {
            printf("shader file broken: %s","check your spaces");
            printf("shader file broken: %s",ex.what());
        }
        if(!tocken_d.compare("fnv"))
        {
            TOCKEN tocken;
            tocken.tocken = LLES_TOCKENS::FUN;
            int y = 0;
            try
            {
                while (!file_tockens[x + y].starts_with("fne"))
                {
                    tocken.value += file_tockens[x + (y + 1)] + ' ';
                    y++;
                }
                x += y;
                tockens.push_back(tocken);
            }
            catch (const std::exception& ex)
            {
                printf("shader file broken: %s","you missed a function close syntax");
                printf("shader file broken: %s",ex.what());
            }
        }
        if(!tocken_d.compare("fni"))
        {
            TOCKEN tocken;
            tocken.tocken = LLES_TOCKENS::FUNI;
            int y = 0;
            try
            {
                while (!file_tockens[x + y].starts_with("fne"))
                {
                    tocken.value += file_tockens[x + (y + 1)] + ' ';
                    y++;
                }
                x += y;
                tockens.push_back(tocken);
            }
            catch (const std::exception& ex)
            {
                printf("shader file broken: %s","you missed a function close syntax");
                printf("shader file broken: %s",ex.what());
            }
        }
        if(!tocken_d.compare("fnf"))
        {
            TOCKEN tocken;
            tocken.tocken = LLES_TOCKENS::FUNF;
            int y = 0;
            try
            {
                while (!file_tockens[x + y].starts_with("fne"))
                {
                    tocken.value += file_tockens[x + (y + 1)] + ' ';
                    y++;
                }
                x += y;
                tockens.push_back(tocken);
            }
            catch (const std::exception& ex)
            {
                printf("shader file broken: %s","you missed a function close syntax");
                printf("shader file broken: %s",ex.what());
            }
        }
        if(!tocken_d.compare("fnd"))
        {
            TOCKEN tocken;
            tocken.tocken = LLES_TOCKENS::FUND;
            int y = 0;
            try
            {
                while (!file_tockens[x + y].starts_with("fne"))
                {
                    tocken.value += file_tockens[x + (y + 1)] + ' ';
                    y++;
                }
                x += y;
                tockens.push_back(tocken);
            }
            catch (const std::exception& ex)
            {
                printf("shader file broken: %s","you missed a function close syntax");
                printf("shader file broken: %s",ex.what());
            }
        }
    }
    return tockens;
}

void LunaLuxEngine::LLEShaderLanguage::parceVariablestoTockens(std::string& value,std::vector<std::string> & file_tocken, std::vector<TOCKEN> & tocken,int& loopVal)
{
    if(!value.compare("float"))
    {
        TOCKEN tocken_d;
        tocken_d.tocken = LLES_TOCKENS::FLT;
        tocken_d.value = file_tocken[loopVal +1] + file_tocken[loopVal + 2] + file_tocken[loopVal + 3];
        loopVal += 3;
        tocken.push_back(tocken_d);
    }
    else if(!value.compare("int"))
    {
        TOCKEN tocken_d;
        tocken_d.tocken = LLES_TOCKENS::INT;
        tocken_d.value = file_tocken[loopVal +1] + file_tocken[loopVal + 2] + file_tocken[loopVal + 3];
        loopVal += 3;
        tocken.push_back(tocken_d);
    }
    else if(!value.compare("double"))
    {
        TOCKEN tocken_d;
        tocken_d.tocken = LLES_TOCKENS::DUB;
        tocken_d.value = file_tocken[loopVal +1] + file_tocken[loopVal + 2] + file_tocken[loopVal + 3];
        loopVal += 3;
        tocken.push_back(tocken_d);
    }
    else if(!value.compare("vec2"))
    {
        TOCKEN tocken_d;
        tocken_d.tocken = LLES_TOCKENS::VEC2;
        tocken_d.value = file_tocken[loopVal +1] + file_tocken[loopVal + 2];
        loopVal += 2;
        tocken.push_back(tocken_d);
    }
    else if(!value.compare("vec3"))
    {
        TOCKEN tocken_d;
        tocken_d.tocken = LLES_TOCKENS::VEC3;
        tocken_d.value = file_tocken[loopVal +1] + file_tocken[loopVal + 2];
        loopVal += 2;
        tocken.push_back(tocken_d);
    }
    else if(!value.compare("mat4"))
    {
        TOCKEN tocken_d;
        tocken_d.tocken = LLES_TOCKENS::MAT4;
        tocken_d.value = file_tocken[loopVal +1] + file_tocken[loopVal + 2];
        loopVal += 2;
        tocken.push_back(tocken_d);
    }
    else return;
}