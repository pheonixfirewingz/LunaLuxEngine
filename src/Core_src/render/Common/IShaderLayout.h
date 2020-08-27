//
// Created by luket on 27/08/2020.
//

#ifndef LUNALUXENGINE_ISHADERLAYOUT_H
#define LUNALUXENGINE_ISHADERLAYOUT_H

#include <vector>
namespace LunaLuxEngine
{
    enum class SHADERLAYOUTTYPE
    {
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        DOUBLE,
        DOUBLE2,
        DOUBLE3,
        DOUBLE4
    };

    class IShaderLayout
    {
    public:
        virtual void setupShaderLayout(std::vector<SHADERLAYOUTTYPE>) = 0;
        virtual void bindLayoutToRenderer() = 0;
        virtual void unbindLayoutToRenderer() = 0;
    };

}
#endif //LUNALUXENGINE_ISHADERLAYOUT_H
