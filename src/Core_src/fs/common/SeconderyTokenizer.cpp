//
// Created by luket on 19/08/2020.
//
#include "ShaderParce.h"
#include "../FileManager.h"

std::vector<LunaLuxEngine::LLEShaderLanguage::TOCKEN> LunaLuxEngine::LLEShaderLanguage::parceSubTockentoTockens(std::string path, bool vertex)
{
    std::vector<TOCKEN> tokens;
    {
        std::vector<TOCKEN> data_x = parceFromFiletoTockens(path, vertex);
        for (int x = 0; x <= data_x.size() - 1; x++)
        {
            TOCKEN token = data_x[x];

            if (token.tocken == LLES_TOCKENS::FUN || token.tocken == LLES_TOCKENS::FUNI ||
                token.tocken == LLES_TOCKENS::FUNF || token.tocken == LLES_TOCKENS::FUND)
            {
                std::vector<std::string> function_data = FileManager::get()->split(token.value, ' ');
                token.value = function_data[0];
                tokens.push_back(token);
                std::remove(function_data.begin(), function_data.end(), "");
                bool in_braket{false};
                TOCKEN tocken_bb;
                tocken_bb.tocken = LLES_TOCKENS::BRAK;
                for (int y = 1; y <= function_data.size() - 1; y++)
                {
                    std::string data = function_data[y];
                    bool found{false};
                    if (data.starts_with("("))
                    {
                        in_braket = true;
                    }
                    if (!in_braket)
                    {
                        if (!data.compare("*"))
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::MUL;
                            tokens.push_back(sub_token);
                            found = true;
                        }

                        if (!data.compare("+"))
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::ADD;
                            tokens.push_back(sub_token);
                            found = true;
                        }

                        if (!data.compare("-"))
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::SUB;
                            tokens.push_back(sub_token);
                            found = true;
                        }

                        if (!data.compare("/"))
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::DIV;
                            tokens.push_back(sub_token);
                            found = true;
                        }

                        if (!data.compare("="))
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::EQL;
                            tokens.push_back(sub_token);
                            found = true;
                        }

                        if (data.starts_with("fne"))
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::FNE;
                            tokens.push_back(sub_token);
                            found = true;
                        }

                        if (!data.compare("glb"))
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::GLB;
                            sub_token.value = function_data[y + 1];
                            y++;
                            tokens.push_back(sub_token);
                            found = true;
                        }

                        if (!data.compare("ret"))
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::RET;
                            tokens.push_back(sub_token);
                            found = true;
                        }

                        if (data.starts_with(";"))
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::LEND;
                            tokens.push_back(sub_token);
                            found = true;
                        }

                        if (!found)
                            found = parceVariablesTokentoTockens(data, function_data, tokens, y);

                        if (!found)
                        {
                            TOCKEN sub_token;
                            sub_token.tocken = LLES_TOCKENS::OTHER;
                            sub_token.value = data;
                            if (!data.empty()) tokens.push_back(sub_token);
                        }
                        token.value = function_data[0];
                    }
                    else
                    {
                        tocken_bb.value += data + " ";
                    }
                    if (data.starts_with(")"))
                    {
                        in_braket = false;
                        tokens.push_back(tocken_bb);
                        tocken_bb.value = "";

                    }
                }
            }
            else
            {
                tokens.push_back(token);
            }
        }
    }
    return tokens;
}

bool LunaLuxEngine::LLEShaderLanguage::parceVariablesTokentoTockens(std::string &value, std::vector<std::string> &file_tocken,
                                                     std::vector<TOCKEN> &tocken, int &loopVal)
{
        if (!value.compare("float"))
        {
            TOCKEN tocken_d;
            tocken_d.tocken = LLES_TOCKENS::FLT;
            tocken_d.value = file_tocken[loopVal + 1] + file_tocken[loopVal + 2] + file_tocken[loopVal + 3];
            loopVal += 3;
            tocken.push_back(tocken_d);
            return true;
        }
        else if (!value.compare("int"))
        {
            TOCKEN tocken_d;
            tocken_d.tocken = LLES_TOCKENS::INT;
            tocken_d.value = file_tocken[loopVal + 1] + file_tocken[loopVal + 2] + file_tocken[loopVal + 3];
            tocken.push_back(tocken_d);
            loopVal += 3;
            return true;
        }
        else if (!value.compare("double"))
        {
            TOCKEN tocken_d;
            tocken_d.tocken = LLES_TOCKENS::DUB;
            tocken_d.value = file_tocken[loopVal + 1] + file_tocken[loopVal + 2] + file_tocken[loopVal + 3];
            tocken.push_back(tocken_d);
            loopVal += 3;
            return true;
        }
        else if (!value.compare("vec2"))
        {
            TOCKEN tocken_d;
            tocken_d.tocken = LLES_TOCKENS::VEC2;
            tocken_d.value = file_tocken[loopVal + 1] + file_tocken[loopVal + 2];
            tocken.push_back(tocken_d);
            loopVal += 2;
            return true;
        }
        else if (!value.compare("vec3"))
        {
            TOCKEN tocken_d;
            tocken_d.tocken = LLES_TOCKENS::VEC3;
            tocken_d.value = file_tocken[loopVal + 1] + file_tocken[loopVal + 2];
            tocken.push_back(tocken_d);
            loopVal += 2;
            return true;
        }
        else if (!value.compare("mat4"))
        {
            TOCKEN tocken_d;
            tocken_d.tocken = LLES_TOCKENS::MAT4;
            tocken_d.value = file_tocken[loopVal + 1] + file_tocken[loopVal + 2];
            loopVal += 2;
            tocken.push_back(tocken_d);
            return true;
        }
        else
        {
            return false;
        }
}