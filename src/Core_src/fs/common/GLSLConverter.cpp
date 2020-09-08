//
// Created by luket on 20/08/2020.
//

#include "ShaderParce.h"

std::string LunaLuxEngine::LLEShaderLanguage::convertToGLSL(std::string path, bool vertex)
{
    std::string data_string = "#version 330 core\n";
    std::vector<TOCKEN> token_v = parceSubTockentoTockens(path,vertex);
    int in_count = 0;
    for(int x =0; x <= token_v.size() - 1;x++)
    {
        TOCKEN token = token_v[x];
        switch (token.tocken)
        {
            case LLES_TOCKENS::IN:
                if(vertex)
                {
                    data_string += " layout (location = " + std::to_string(in_count) + ") in " + token.value;
                    in_count++;
                }
                else data_string += "in " + token.value;
                break;
            case LLES_TOCKENS::OUT:
                data_string += " out " + token.value;
                break;
            case LLES_TOCKENS::UNF:
                data_string += " uniform " + token.value;
                break;
            case LLES_TOCKENS::FUN:
                data_string += " void " + token.value + std::string (token_v[x + 1].value + "\n{ \n");
                x++;
                break;
            case LLES_TOCKENS::FUNI:
                data_string += " int " + token.value + std::string (token_v[x + 1].value + "\n{ \n");
                x++;
                break;
            case LLES_TOCKENS::FUNF:
                data_string += " float " + token.value + std::string (token_v[x + 1].value + "\n{ \n");
                x++;
                break;
            case LLES_TOCKENS::INT:
                data_string += " int " + token.value;
                break;
            case LLES_TOCKENS::FLT:
                data_string += " float " + token.value;
                break;
            case LLES_TOCKENS::DUB:
                data_string += " double " + token.value;
                break;
            case LLES_TOCKENS::MAT4:
                data_string += " mat4 " + token.value;
                break;
            case LLES_TOCKENS::VEC3:
                data_string += " vec3 " + token.value;
                break;
            case LLES_TOCKENS::VEC2:
                data_string += " vec2 " + token.value;
                break;
            case LLES_TOCKENS::MUL:
                data_string += " * ";
                break;
            case LLES_TOCKENS::DIV:
                data_string += " / ";
                break;
            case LLES_TOCKENS::SUB:
                data_string += " - ";
                break;
            case LLES_TOCKENS::ADD:
                data_string += " + ";
                break;
            case LLES_TOCKENS::EQL:
                data_string += " = ";
                break;
            case LLES_TOCKENS::GLB:
                data_string += " gl_Position ";
                break;
            case LLES_TOCKENS::RET:
                data_string += " return ";
                break;
            case LLES_TOCKENS::OTHER:
                data_string += token.value;
                break;
            case LLES_TOCKENS::FNE:
                data_string += "}\n";
                break;
            case LLES_TOCKENS::LEND:
                data_string += ";\n";
                break;

        }
    }
    return data_string;
}

