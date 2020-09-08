//
// Created by luket on 27/08/2020.
//

#include "OpenGLShaderLayout.h"
#include "glad.h"

void LunaLuxEngine::OpenGLShaderLayout::setupShaderLayout(std::vector<SHADERLAYOUTTYPE> vector)
{
    int m_temp = 0;
    for (int x = 0; x <= vector.size() - 1; x++)
    {
        SHADERLAYOUTTYPE token = vector[x];
        switch (token)
        {
            case SHADERLAYOUTTYPE::FLOAT:m_count++;
                m_temp++;
                break;
            case SHADERLAYOUTTYPE::FLOAT2:m_count++;
                m_temp += 2;
                break;
            case SHADERLAYOUTTYPE::FLOAT3:m_count++;
                m_temp += 3;
                break;
            case SHADERLAYOUTTYPE::FLOAT4:m_count++;
                m_temp += 4;
                break;
        }
    }
    int m_temp_v = 0;
    for (int x = 0; x <= vector.size() - 1; x++)
    {
        SHADERLAYOUTTYPE token = vector[x];
        switch (token)
        {
            case SHADERLAYOUTTYPE::FLOAT:
                glVertexAttribPointer(x, 1, GL_FLOAT, GL_FALSE, m_temp * sizeof(float), (void *)(m_temp_v * sizeof(float)));
                m_temp_v++;
                break;
            case SHADERLAYOUTTYPE::FLOAT2:
                glVertexAttribPointer(x, 2, GL_FLOAT, GL_FALSE, m_temp * sizeof(float), (void *)(m_temp_v * sizeof(float)));
                m_temp_v += 2;
                break;
            case SHADERLAYOUTTYPE::FLOAT3:
                glVertexAttribPointer(x, 3, GL_FLOAT, GL_FALSE, m_temp * sizeof(float), (void *)(m_temp_v * sizeof(float)));
                m_temp_v += 3;
                break;
            case SHADERLAYOUTTYPE::FLOAT4:
                glVertexAttribPointer(x, 3, GL_FLOAT, GL_FALSE, m_temp * sizeof(float), (void *)(m_temp_v * sizeof(float)));
                m_temp_v += 4;
                break;
        }
    }
}

void LunaLuxEngine::OpenGLShaderLayout::bindLayoutToRenderer()
{
    for (int x = 0; x <= m_count; x++)
        glEnableVertexAttribArray(x);
}

void LunaLuxEngine::OpenGLShaderLayout::unbindLayoutToRenderer()
{
    for (int x = 0; x <= m_count; x++)
        glDisableVertexAttribArray(x);
}