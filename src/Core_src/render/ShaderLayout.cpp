//
// Created by luket on 27/08/2020.
//

#include "ShaderLayout.h"

void LunaLuxEngine::ShaderLayout::setupShaderLayout(std::vector<SHADERLAYOUTTYPE> type)
{
    shaderLayout->setupShaderLayout(type);
}

void LunaLuxEngine::ShaderLayout::bindLayoutToRenderer()
{
    shaderLayout->bindLayoutToRenderer();
}

void LunaLuxEngine::ShaderLayout::unbindLayoutToRenderer()
{
    shaderLayout->unbindLayoutToRenderer();
}
