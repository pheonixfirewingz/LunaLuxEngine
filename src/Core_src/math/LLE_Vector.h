//
// Created by luket on 25/08/2020.
//

#ifndef LUNALUXENGINE_LLE_VECTOR_H
#define LUNALUXENGINE_LLE_VECTOR_H
namespace LunaLuxEngine
{
    struct vector2f
    {
        float vec[2];

        vector2f(float x,float y)
        {
            vec[0] = x;
            vec[1] = y;
        }

        float* getData();
        float getX();
        float getY();
    };

    struct vector3f
    {
        float vec[3];

        vector3f(float x,float y,float z)
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
        }

        float* getData();
        float getX();
        float getY();
        float getZ();
    };

    struct vector4f
    {
        float vec[4];

        vector4f(float x,float y,float z,float w)
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
            vec[3] = w;
        }

        float* getData();
        float getX();
        float getY();
        float getZ();
        float getW();
    };

    struct vector2d
    {
        double vec[2];
        vector2d(vector2d *pD)
        {
            vec[0] = pD->getX();
            vec[1] = pD->getY();
        }

        vector2d(double x,double y)
        {
            vec[0] = x;
            vec[1] = y;
        }

        double * getData();
        double getX();
        double getY();
    };

    struct vector3d
    {
        double vec[3];

        vector3d(vector3d *pD)
        {
            vec[0] = pD->getX();
            vec[1] = pD->getY();
            vec[2] = pD->getZ();
        }

        vector3d(double x,double y,double z)
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
        }

        double * getData();
        double getX();
        double getY();
        double getZ();
    };

    struct vector4d
    {
        double vec[4];

        vector4d(vector4d *pD)
        {
            vec[0] = pD->getX();
            vec[1] = pD->getY();
            vec[2] = pD->getZ();
            vec[3] = pD->getW();
        }

        vector4d(double x,double y,double z,double w)
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
            vec[3] = w;
        }

        double * getData();
        double getX();
        double getY();
        double getZ();
        double getW();
    };

    typedef vector2d vec2d;
    typedef vector3d vec3d;
    typedef vector4d vec4d;

    typedef vector2f vec2f;
    typedef vector3f vec3f;
    typedef vector4f vec4f;
}
#endif //LUNALUXENGINE_LLE_VECTOR_H
