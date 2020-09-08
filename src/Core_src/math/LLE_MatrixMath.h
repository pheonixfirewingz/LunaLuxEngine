//
// Created by luket on 27/08/2020.
//

#ifndef LUNALUXENGINE_LLE_MATRIXMATH_H
#define LUNALUXENGINE_LLE_MATRIXMATH_H
#include "LLE_Matrix.h"

namespace LunaLuxEngine
{
#ifdef LLE_WINDOWS
    [[maybe_unused]] mat4d m_add(mat4d,mat4d);

    [[maybe_unused]] mat4d m_sub(mat4d,mat4d);

    [[maybe_unused]] mat4d m_div(mat4d,mat4d);

    [[maybe_unused]] mat4d m_mul(mat4d,mat4d);
#endif
}

#endif //LUNALUXENGINE_LLE_MATRIXMATH_H
