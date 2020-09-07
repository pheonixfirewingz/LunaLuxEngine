//
// Created by luket on 25/08/2020.
//

#include "LLE_VectorMath.h"
#ifdef LLE_WINDOWS
#include <intrin.h>


[[maybe_unused]] LunaLuxEngine::vec2d LunaLuxEngine::v_add(LunaLuxEngine::vec2d in_1, LunaLuxEngine::vec2d in_2)
{
    __m256d vec1,vec2,vec3;
    vec1 = _mm256_set_pd(in_1.getX(), in_1.getY(), 0.0, 0.0);
    vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),0.0,0.0);
    vec3 = _mm256_add_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec2d(data[3],data[2]);
}

[[maybe_unused]] LunaLuxEngine::vec3d LunaLuxEngine::v_add(LunaLuxEngine::vec3d in_1, LunaLuxEngine::vec3d in_2)
{
    __m256d vec1,vec2,vec3;
    vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),in_1.getZ(),0.0);
    vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),in_2.getZ(),0.0);
    vec3 = _mm256_add_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec3d(data[3],data[2],data[1]);
}

[[maybe_unused]] LunaLuxEngine::vec4d LunaLuxEngine::v_add(LunaLuxEngine::vec4d in_1, LunaLuxEngine::vec4d in_2)
{
    __m256d vec1,vec2,vec3;
    vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),in_1.getZ(),in_1.getW());
    vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),in_2.getZ(),in_2.getW());
    vec3 = _mm256_add_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec4d(data[3],data[2],data[1],data[0]);
}

[[maybe_unused]] LunaLuxEngine::vec2d LunaLuxEngine::v_sub(LunaLuxEngine::vec2d in_1, LunaLuxEngine::vec2d in_2)
{
    __m256d vec1,vec2,vec3;
    vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),0.0,0.0);
    vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),0.0,0.0);
    vec3 = _mm256_sub_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec2d(data[3],data[2]);
}

[[maybe_unused]] LunaLuxEngine::vec3d LunaLuxEngine::v_sub(LunaLuxEngine::vec3d in_1, LunaLuxEngine::vec3d in_2)
{
    __m256d vec1,vec2,vec3;
    vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),in_1.getZ(),0.0);
    vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),in_2.getZ(),0.0);
    vec3 = _mm256_sub_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec3d(data[3],data[2],data[1]);
}

[[maybe_unused]] LunaLuxEngine::vec4d LunaLuxEngine::v_sub(LunaLuxEngine::vec4d in_1, LunaLuxEngine::vec4d in_2)
{
    __m256d vec1,vec2,vec3;
    vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),in_1.getZ(),in_1.getW());
    vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),in_2.getZ(),in_2.getW());
    vec3 = _mm256_sub_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec4d(data[3],data[2],data[1],data[0]);
}

[[maybe_unused]] LunaLuxEngine::vec2d LunaLuxEngine::v_div(LunaLuxEngine::vec2d in_1, LunaLuxEngine::vec2d in_2)
{
    __m256d vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),0.0,0.0);
    __m256d vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),0.0,0.0);
    __m256d vec3 = _mm256_div_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec2d(data[3],data[2]);
}

[[maybe_unused]] LunaLuxEngine::vec3d LunaLuxEngine::v_div(LunaLuxEngine::vec3d in_1, LunaLuxEngine::vec3d in_2)
{
    __m256d vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),in_1.getZ(),0.0);
    __m256d vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),in_2.getZ(),0.0);
    __m256d vec3 = _mm256_div_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec3d(data[3],data[2],data[1]);
}

[[maybe_unused]] LunaLuxEngine::vec4d LunaLuxEngine::v_div(LunaLuxEngine::vec4d in_1, LunaLuxEngine::vec4d in_2)
{
    __m256d vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),in_1.getZ(),in_1.getW());
    __m256d vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),in_2.getZ(),in_2.getW());
    __m256d vec3 = _mm256_div_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec4d(data[3],data[2],data[1],data[0]);
}

[[maybe_unused]] LunaLuxEngine::vec2d LunaLuxEngine::v_mul(LunaLuxEngine::vec2d in_1, LunaLuxEngine::vec2d in_2)
{
    __m256d vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),0.0,0.0);
    __m256d vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),0.0,0.0);
    __m256d vec3 = _mm256_mul_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec2d(data[3],data[2]);
}

[[maybe_unused]] LunaLuxEngine::vec3d LunaLuxEngine::v_mul(LunaLuxEngine::vec3d in_1, LunaLuxEngine::vec3d in_2)
{
    __m256d vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),in_1.getZ(),0.0);
    __m256d vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),in_2.getZ(),0.0);
    __m256d vec3 = _mm256_mul_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec3d(data[3],data[2],data[1]);
}

[[maybe_unused]] LunaLuxEngine::vec4d LunaLuxEngine::v_mul(LunaLuxEngine::vec4d in_1, LunaLuxEngine::vec4d in_2)
{
    __m256d vec1 = _mm256_set_pd(in_1.getX(),in_1.getY(),in_1.getZ(),in_1.getW());
    __m256d vec2 = _mm256_set_pd(in_2.getX(),in_2.getY(),in_2.getZ(),in_2.getW());
    __m256d vec3 = _mm256_mul_pd(vec1,vec2);
    auto* data = (double*)&vec3;
    return LunaLuxEngine::vec4d(data[3],data[2],data[1],data[0]);
}
/*
LunaLuxEngine::vec2f LunaLuxEngine::v_add(LunaLuxEngine::vec2f, LunaLuxEngine::vec2f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec2f(data[3],data[2]);
}

[[maybe_unused]] LunaLuxEngine::vec3f LunaLuxEngine::v_add(LunaLuxEngine::vec3f, LunaLuxEngine::vec3f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec3f(data[3],data[2],data[1]);
}

[[maybe_unused]] LunaLuxEngine::vec4f LunaLuxEngine::v_add(LunaLuxEngine::vec4f, LunaLuxEngine::vec4f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec4f(data[0],data[1],data[2],data[3]);
}

[[maybe_unused]] LunaLuxEngine::vec2f LunaLuxEngine::v_sub(LunaLuxEngine::vec2f, LunaLuxEngine::vec2f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec2f(data[3],data[2]);
}

[[maybe_unused]] LunaLuxEngine::vec3f LunaLuxEngine::v_sub(LunaLuxEngine::vec3f, LunaLuxEngine::vec3f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec3f(data[3],data[2],data[1]);
}

[[maybe_unused]] LunaLuxEngine::vec4f LunaLuxEngine::v_sub(LunaLuxEngine::vec4f, LunaLuxEngine::vec4f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec4f(data[0],data[1],data[2],data[3]);
}

[[maybe_unused]] LunaLuxEngine::vec2f LunaLuxEngine::v_div(LunaLuxEngine::vec2f, LunaLuxEngine::vec2f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec2f(data[3],data[2]);
}

[[maybe_unused]] LunaLuxEngine::vec3f LunaLuxEngine::v_div(LunaLuxEngine::vec3f, LunaLuxEngine::vec3f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec3f(data[3],data[2],data[1]);
}

[[maybe_unused]] LunaLuxEngine::vec4f LunaLuxEngine::v_div(LunaLuxEngine::vec4f, LunaLuxEngine::vec4f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec4f(data[0],data[1],data[2],data[3]);
}

[[maybe_unused]] LunaLuxEngine::vec2f LunaLuxEngine::v_mul(LunaLuxEngine::vec2f, LunaLuxEngine::vec2f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec2f(data[3],data[2]);
}

[[maybe_unused]] LunaLuxEngine::vec3f LunaLuxEngine::v_mul(LunaLuxEngine::vec3f, LunaLuxEngine::vec3f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec3f(data[3],data[2],data[1]);
}

[[maybe_unused]] LunaLuxEngine::vec4f LunaLuxEngine::v_mul(LunaLuxEngine::vec4f, LunaLuxEngine::vec4f)
{
    __m128 vec1;
    __m128 vec2;
    __m128 vec3;
    auto* data = (float*)&vec3;
    return LunaLuxEngine::vec4f(data[0],data[1],data[2],data[3]);
}
*/
#endif