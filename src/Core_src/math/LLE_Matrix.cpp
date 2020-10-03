//
// Created by luket on 26/08/2020.
//

#include "LLE_Matrix.h"

float LunaLuxEngine::matrix4f::get(int val)
{
    return mat[val];
}

void LunaLuxEngine::matrix4f::zero()
{
    for(int x = 0; x <= 16; x++) mat[x] = 0.0f;
}

void LunaLuxEngine::matrix4f::identity()
{
    mat[0] = 1.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;
    mat[4] = 0.0f;
    mat[5] = 1.0f;
    mat[6] = 0.0f;
    mat[7] = 0.0f;
    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

void LunaLuxEngine::matrix4d::identity()
{
    mat[0] = 1.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;
    mat[4] = 0.0f;
    mat[5] = 1.0f;
    mat[6] = 0.0f;
    mat[7] = 0.0f;
    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

double LunaLuxEngine::matrix4d::get(int val)
{
    return mat[val];
}

void LunaLuxEngine::matrix4d::zero()
{
    for(int x = 0; x <= 16; x++) mat[x] = 0.0f;
}

void LunaLuxEngine::matrix4d::translate(LunaLuxEngine::vector3d vec, LunaLuxEngine::matrix4d src)
{

}
