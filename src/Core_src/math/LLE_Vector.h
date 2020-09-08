//
// Created by luket on 25/08/2020.
//

#ifndef LUNALUXENGINE_LLE_VECTOR_H
#define LUNALUXENGINE_LLE_VECTOR_H
#include <LLESDK/types.h>
namespace LunaLuxEngine
{
    struct vector2f
    {
        float vec[2]{};

        [[maybe_unused]] vector2f(float x,float y)
        {
            vec[0] = x;
            vec[1] = y;
        }

        [[maybe_unused]] float* getData();
        float getX();

        [[maybe_unused]] float getY();
    };

    struct vector3f
    {
        float vec[3]{};

        [[maybe_unused]] vector3f(float x,float y,float z)
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
        }

        [[maybe_unused]] float* getData();
        float getX();

        [[maybe_unused]] float getY();

        [[maybe_unused]] float getZ();
    };

    struct vector4f
    {
        float vec[4]{};

        [[maybe_unused]] vector4f(float x,float y,float z,float w)
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
            vec[3] = w;
        }

        [[maybe_unused]] float* getData();
        float getX();

        [[maybe_unused]] float getY();

        [[maybe_unused]] float getZ();
        float getW();
    };

    struct vector2d
    {
        double vec[2]{};

        [[maybe_unused]] explicit vector2d(vector2d *pD)
        {
            vec[0] = pD->getX();
            vec[1] = pD->getY();
        }

        [[maybe_unused]] vector2d(double x,double y)
        {
            vec[0] = x;
            vec[1] = y;
        }

        [[maybe_unused]] double * getData();
        double getX();
        double getY();
    };

    struct vector3d
    {
        double vec[3]{};

        [[maybe_unused]] explicit vector3d(vector3d *pD)
        {
            vec[0] = pD->getX();
            vec[1] = pD->getY();
            vec[2] = pD->getZ();
        }

        [[maybe_unused]] vector3d(double x,double y,double z)
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
        }

        [[maybe_unused]] double * getData();
        double getX();
        double getY();
        double getZ();
    };

    struct vector4d
    {
        double vec[4]{};

        [[maybe_unused]] explicit vector4d(vector4d *pD)
        {
            vec[0] = pD->getX();
            vec[1] = pD->getY();
            vec[2] = pD->getZ();
            vec[3] = pD->getW();
        }

        [[maybe_unused]] vector4d(double x,double y,double z,double w)
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
            vec[3] = w;
        }

        [[maybe_unused]] double * getData();
        double getX();
        double getY();
        double getZ();
        double getW();
    };

    [[maybe_unused]] typedef vector2d vec2d;
    [[maybe_unused]] typedef vector3d vec3d;
    [[maybe_unused]] typedef vector4d vec4d;

    [[maybe_unused]] typedef vector2f vec2f;
    [[maybe_unused]] typedef vector3f vec3f;
    [[maybe_unused]] typedef vector4f vec4f;
}
#endif //LUNALUXENGINE_LLE_VECTOR_H
