//
// Created by luket on 25/08/2020.
//
#include "LLE_Vector.h"

double LunaLuxEngine::vector2d::getX()
{
    return vec[0];
}

double LunaLuxEngine::vector2d::getY()
{
    return vec[1];
}

double LunaLuxEngine::vector3d::getX()
{
    return vec[0];
}

double LunaLuxEngine::vector3d::getY()
{
    return vec[1];
}

double LunaLuxEngine::vector3d::getZ()
{
    return vec[2];
}

double LunaLuxEngine::vector4d::getX()
{
    return vec[0];
}

double LunaLuxEngine::vector4d::getY()
{
    return vec[1];
}

double LunaLuxEngine::vector4d::getZ()
{
    return vec[2];
}

double LunaLuxEngine::vector4d::getW()
{
    return vec[3];
}

[[maybe_unused]] double *LunaLuxEngine::vector2d::getData()
{
    return vec;
}

[[maybe_unused]] double *LunaLuxEngine::vector3d::getData()
{
    return vec;
}

[[maybe_unused]] double *LunaLuxEngine::vector4d::getData()
{
    return vec;
}

float LunaLuxEngine::vector2f::getX()
{
    return vec[0];
}

[[maybe_unused]] float LunaLuxEngine::vector2f::getY()
{
    return vec[1];
}

float LunaLuxEngine::vector3f::getX()
{
    return vec[0];
}

[[maybe_unused]] float LunaLuxEngine::vector3f::getY()
{
    return vec[1];
}

[[maybe_unused]] float LunaLuxEngine::vector3f::getZ()
{
    return vec[2];
}

float LunaLuxEngine::vector4f::getX()
{
    return vec[0];
}

[[maybe_unused]] float LunaLuxEngine::vector4f::getY()
{
    return vec[1];
}

[[maybe_unused]] float LunaLuxEngine::vector4f::getZ()
{
    return vec[2];
}

float LunaLuxEngine::vector4f::getW()
{
    return vec[3];
}

[[maybe_unused]] float *LunaLuxEngine::vector2f::getData()
{
    return vec;
}

[[maybe_unused]] float *LunaLuxEngine::vector3f::getData()
{
    return vec;
}

[[maybe_unused]] float *LunaLuxEngine::vector4f::getData()
{
    return vec;
}