//
// Created by luket on 27/08/2020.
//

#include "LLE_MatrixMath.h"
#ifdef LLE_WINDOWS
#include <intrin.h>

[[maybe_unused]] LunaLuxEngine::mat4d LunaLuxEngine::m_add(LunaLuxEngine::mat4d in_0, LunaLuxEngine::mat4d in_1)
{
    double temp[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    __m256d row = _mm256_set_pd(in_0.get(0), in_0.get(1), in_0.get(2), in_0.get(3));
    __m256d row2 = _mm256_set_pd(in_1.get(0), in_1.get(1), in_1.get(2), in_1.get(3));
    __m256d new_row = _mm256_add_pd(row,row2);

    __m256d row_ = _mm256_set_pd(in_0.get(4), in_0.get(5), in_0.get(6), in_0.get(7));
    __m256d row2_ = _mm256_set_pd(in_1.get(4), in_1.get(5), in_1.get(6), in_1.get(7));
    __m256d new_row_ = _mm256_add_pd(row_,row2_);

    auto* data = (double*)&new_row;
    auto* data2 = (double*)&new_row_;

    temp[0] = data[3];
    temp[1] = data[2];
    temp[2] = data[1];
    temp[3] = data[0];
    temp[4] = data2[3];
    temp[5] = data2[2];
    temp[6] = data2[1];
    temp[7] = data2[0];

    __m256d row__ = _mm256_set_pd(in_0.get(8), in_0.get(9), in_0.get(10), in_0.get(11));
    __m256d row2__ = _mm256_set_pd(in_1.get(8), in_1.get(9), in_1.get(10), in_1.get(11));
    __m256d new_row__ = _mm256_add_pd(row__,row2__);

    __m256d _row_ = _mm256_set_pd(in_0.get(12), in_0.get(13), in_0.get(14), in_0.get(15));
    __m256d _row2_ = _mm256_set_pd(in_1.get(12), in_1.get(13), in_1.get(14), in_1.get(15));
    __m256d _new_row_ = _mm256_add_pd(_row_,_row2_);

    auto* data3 = (double*)&new_row__;
    auto* data4 = (double*)&_new_row_;

    temp[8] = data3[3];
    temp[9] = data3[2];
    temp[10] = data3[1];
    temp[11] = data3[0];
    temp[12] = data4[3];
    temp[13] = data4[2];
    temp[14] = data4[1];
    temp[15] = data4[0];

    return LunaLuxEngine::mat4d(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],
                                temp[8],temp[9],temp[10],temp[11],temp[12],temp[13],temp[14],temp[15]);
}

[[maybe_unused]] LunaLuxEngine::mat4d LunaLuxEngine::m_sub(LunaLuxEngine::mat4d in_0, LunaLuxEngine::mat4d in_1)
{
    double temp[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    __m256d row = _mm256_set_pd(in_0.get(0), in_0.get(1), in_0.get(2), in_0.get(3));
    __m256d row2 = _mm256_set_pd(in_1.get(0), in_1.get(1), in_1.get(2), in_1.get(3));
    __m256d new_row = _mm256_sub_pd(row,row2);

    __m256d row_ = _mm256_set_pd(in_0.get(4), in_0.get(5), in_0.get(6), in_0.get(7));
    __m256d row2_ = _mm256_set_pd(in_1.get(4), in_1.get(5), in_1.get(6), in_1.get(7));
    __m256d new_row_ = _mm256_sub_pd(row_,row2_);

    auto* data = (double*)&new_row;
    auto* data2 = (double*)&new_row_;

    temp[0] = data[3];
    temp[1] = data[2];
    temp[2] = data[1];
    temp[3] = data[0];
    temp[4] = data2[3];
    temp[5] = data2[2];
    temp[6] = data2[1];
    temp[7] = data2[0];

    __m256d row__ = _mm256_set_pd(in_0.get(8), in_0.get(9), in_0.get(10), in_0.get(11));
    __m256d row2__ = _mm256_set_pd(in_1.get(8), in_1.get(9), in_1.get(10), in_1.get(11));
    __m256d new_row__ = _mm256_sub_pd(row__,row2__);

    __m256d _row_ = _mm256_set_pd(in_0.get(12), in_0.get(13), in_0.get(14), in_0.get(15));
    __m256d _row2_ = _mm256_set_pd(in_1.get(12), in_1.get(13), in_1.get(14), in_1.get(15));
    __m256d _new_row_ = _mm256_sub_pd(_row_,_row2_);

    auto* data3 = (double*)&new_row__;
    auto* data4 = (double*)&_new_row_;

    temp[8] = data3[3];
    temp[9] = data3[2];
    temp[10] = data3[1];
    temp[11] = data3[0];
    temp[12] = data4[3];
    temp[13] = data4[2];
    temp[14] = data4[1];
    temp[15] = data4[0];

    return LunaLuxEngine::mat4d(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],
                                temp[8],temp[9],temp[10],temp[11],temp[12],temp[13],temp[14],temp[15]);
}

[[maybe_unused]] LunaLuxEngine::mat4d LunaLuxEngine::m_div(LunaLuxEngine::mat4d in_0, LunaLuxEngine::mat4d in_1)
{
    double temp[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    __m256d row = _mm256_set_pd(in_0.get(0), in_0.get(1), in_0.get(2), in_0.get(3));
    __m256d row2 = _mm256_set_pd(in_1.get(0), in_1.get(1), in_1.get(2), in_1.get(3));
    __m256d new_row = _mm256_div_pd(row,row2);

    __m256d row_ = _mm256_set_pd(in_0.get(4), in_0.get(5), in_0.get(6), in_0.get(7));
    __m256d row2_ = _mm256_set_pd(in_1.get(4), in_1.get(5), in_1.get(6), in_1.get(7));
    __m256d new_row_ = _mm256_div_pd(row_,row2_);

    auto* data = (double*)&new_row;
    auto* data2 = (double*)&new_row_;

    temp[0] = data[3];
    temp[1] = data[2];
    temp[2] = data[1];
    temp[3] = data[0];
    temp[4] = data2[3];
    temp[5] = data2[2];
    temp[6] = data2[1];
    temp[7] = data2[0];

    __m256d row__ = _mm256_set_pd(in_0.get(8), in_0.get(9), in_0.get(10), in_0.get(11));
    __m256d row2__ = _mm256_set_pd(in_1.get(8), in_1.get(9), in_1.get(10), in_1.get(11));
    __m256d new_row__ = _mm256_div_pd(row__,row2__);

    __m256d _row_ = _mm256_set_pd(in_0.get(12), in_0.get(13), in_0.get(14), in_0.get(15));
    __m256d _row2_ = _mm256_set_pd(in_1.get(12), in_1.get(13), in_1.get(14), in_1.get(15));
    __m256d _new_row_ = _mm256_div_pd(_row_,_row2_);

    auto* data3 = (double*)&new_row__;
    auto* data4 = (double*)&_new_row_;

    temp[8] = data3[3];
    temp[9] = data3[2];
    temp[10] = data3[1];
    temp[11] = data3[0];
    temp[12] = data4[3];
    temp[13] = data4[2];
    temp[14] = data4[1];
    temp[15] = data4[0];

    return LunaLuxEngine::mat4d(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],
                                temp[8],temp[9],temp[10],temp[11],temp[12],temp[13],temp[14],temp[15]);
}

[[maybe_unused]] LunaLuxEngine::mat4d LunaLuxEngine::m_mul(LunaLuxEngine::mat4d in_0, LunaLuxEngine::mat4d in_1)
{
    double temp[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    __m256d row = _mm256_set_pd(in_0.get(0), in_0.get(1), in_0.get(2), in_0.get(3));
    __m256d row2 = _mm256_set_pd(in_1.get(0), in_1.get(1), in_1.get(2), in_1.get(3));
    __m256d new_row = _mm256_mul_pd(row,row2);

    __m256d row_ = _mm256_set_pd(in_0.get(4), in_0.get(5), in_0.get(6), in_0.get(7));
    __m256d row2_ = _mm256_set_pd(in_1.get(4), in_1.get(5), in_1.get(6), in_1.get(7));
    __m256d new_row_ = _mm256_mul_pd(row_,row2_);

    auto* data = (double*)&new_row;
    auto* data2 = (double*)&new_row_;

    temp[0] = data[3];
    temp[1] = data[2];
    temp[2] = data[1];
    temp[3] = data[0];
    temp[4] = data2[3];
    temp[5] = data2[2];
    temp[6] = data2[1];
    temp[7] = data2[0];

    __m256d row__ = _mm256_set_pd(in_0.get(8), in_0.get(9), in_0.get(10), in_0.get(11));
    __m256d row2__ = _mm256_set_pd(in_1.get(8), in_1.get(9), in_1.get(10), in_1.get(11));
    __m256d new_row__ = _mm256_mul_pd(row__,row2__);

    __m256d _row_ = _mm256_set_pd(in_0.get(12), in_0.get(13), in_0.get(14), in_0.get(15));
    __m256d _row2_ = _mm256_set_pd(in_1.get(12), in_1.get(13), in_1.get(14), in_1.get(15));
    __m256d _new_row_ = _mm256_mul_pd(_row_,_row2_);

    auto* data3 = (double*)&new_row__;
    auto* data4 = (double*)&_new_row_;

    temp[8] = data3[3];
    temp[9] = data3[2];
    temp[10] = data3[1];
    temp[11] = data3[0];
    temp[12] = data4[3];
    temp[13] = data4[2];
    temp[14] = data4[1];
    temp[15] = data4[0];

    return LunaLuxEngine::mat4d(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],
                                temp[8],temp[9],temp[10],temp[11],temp[12],temp[13],temp[14],temp[15]);
}
#endif