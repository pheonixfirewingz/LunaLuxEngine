//
// Created by luket on 26/08/2020.
//

#ifndef LUNALUXENGINE_LLE_MATRIX_H
#define LUNALUXENGINE_LLE_MATRIX_H
#include "LLE_Vector.h"
namespace LunaLuxEngine
{
    struct matrix4f
    {
        float mat[16];

        float get(int val);
        void zero();
        void identity();

        matrix4f()
        {
            zero();
        }

        matrix4f(matrix4f *pd)
        {
            mat[0] = pd->get(0);
            mat[1] = pd->get(1);
            mat[2] = pd->get(2);
            mat[3] = pd->get(3);

            mat[4] = pd->get(4);
            mat[5] = pd->get(5);
            mat[6] = pd->get(6);
            mat[7] = pd->get(7);

            mat[8]  = pd->get(8);
            mat[9]  = pd->get(9);
            mat[10] = pd->get(10);
            mat[11] = pd->get(11);

            mat[12]  = pd->get(12);
            mat[13]  = pd->get(13);
            mat[14] = pd->get(14);
            mat[15] = pd->get(15);
        }

        matrix4f(float m0,float m1,float m2,float m3,float m4,float m5,float m6,float m7,
                float m8,float m9,float m10,float m11,float m12,float m13,float m14,float m15)
        {
            mat[0] = m0;
            mat[1] = m1;
            mat[2] = m2;
            mat[3] = m3;

            mat[4] = m4;
            mat[5] = m5;
            mat[6] = m6;
            mat[7] = m7;

            mat[8]  = m8;
            mat[9]  = m9;
            mat[10] = m10;
            mat[11] = m11;

            mat[12] = m12;
            mat[13] = m13;
            mat[14] = m14;
            mat[15] = m15;
        }
    };

    struct matrix4d
    {
        double mat[16];


        double get(int val);
        void zero();
        void identity();
        void translate(vector3d,matrix4d);

        matrix4d()
        {
            zero();
        }

        matrix4d(matrix4d *pd)
        {
            mat[0] = pd->get(0);
            mat[1] = pd->get(1);
            mat[2] = pd->get(2);
            mat[3] = pd->get(3);

            mat[4] = pd->get(4);
            mat[5] = pd->get(5);
            mat[6] = pd->get(6);
            mat[7] = pd->get(7);

            mat[8]  = pd->get(8);
            mat[9]  = pd->get(9);
            mat[10] = pd->get(10);
            mat[11] = pd->get(11);

            mat[12]  = pd->get(12);
            mat[13]  = pd->get(13);
            mat[14] = pd->get(14);
            mat[15] = pd->get(15);
        }

        matrix4d(double m0,double m1,double m2,double m3,double m4,double m5,double m6,double m7,
                 double m8,double m9,double m10,double m11,double m12,double m13,double m14,double m15)
        {
            mat[0] = m0;
            mat[1] = m1;
            mat[2] = m2;
            mat[3] = m3;

            mat[4] = m4;
            mat[5] = m5;
            mat[6] = m6;
            mat[7] = m7;

            mat[8]  = m8;
            mat[9]  = m9;
            mat[10] = m10;
            mat[11] = m11;

            mat[12] = m12;
            mat[13] = m13;
            mat[14] = m14;
            mat[15] = m15;
        }
    };

    typedef matrix4f mat4f;
    typedef matrix4d mat4d;
}
#endif //LUNALUXENGINE_LLE_MATRIX_H
