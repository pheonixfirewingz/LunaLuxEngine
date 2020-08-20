//
// Created by luket on 19/08/2020.
//

#include "ShaderParce.h"

std::string LunaLuxEngine::LLEShaderLanguage::parceFileToShader(std::string path, bool glsl, bool vertex)
{
    if (glsl) return convertToGLSL(path, vertex);
    else return std::string("ERROR:NOT SUPPORTED");
}