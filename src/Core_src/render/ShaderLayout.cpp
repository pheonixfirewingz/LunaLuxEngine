//
// Created by luket on 27/08/2020.
//

#include "ShaderLayout.h"
#include "OpenGL/OpenGLShaderLayout.h"

LunaLuxEngine::ShaderLayout::ShaderLayout()
{
    shaderLayout = new OpenGLShaderLayout();
}

LunaLuxEngine::ShaderLayout::ShaderLayout(std::vector<LunaLuxEngine::SHADERLAYOUTTYPE> types,LunaLuxEngine::Buffer* buffer)
{
    shaderLayout = new OpenGLShaderLayout();
    buffer->bindV();
    setupShaderLayout(types);
    buffer->unBindV();
}

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
