//
// Created by luket on 01/09/2020.
//

#ifndef LUNALUXENGINE_IENTITY_H
#define LUNALUXENGINE_IENTITY_H
#include "../../math/LLE_Vector.h"

namespace LunaLuxEngine
{
    class IEntity
    {
    protected:
        vector3f m_position = vector3f(0.0f,0.0f,0.0f);
        vector3f m_rotation = vector3f(0.0f,0.0f,0.0f);
        vector3f m_scale    = vector3f(0.0f,0.0f,0.0f);
    public:
        virtual void onBaseCreate()  = 0;

        virtual void onUpdate()      = 0;

        virtual void onDestroy()     = 0;
    };
}
#endif //LUNALUXENGINE_IENTITY_H
