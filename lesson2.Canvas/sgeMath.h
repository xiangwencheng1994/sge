/**
 *  sgeMath.h
 *  用于定义一些常用数学结构和函数
 */
#ifndef SGE_MATH_H
#define SGE_MATH_H

#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#pragma pack(push)
#pragma pack(1)

namespace sge
{
    typedef unsigned char           byte;
    typedef int                     sizei;

    /**
     *  用3个float表示颜色
     *  内存分别为Red,Green,Blue
     *  每个分量的理论范围为0-1
     */
    struct Color3f
    {
        float   _red;
        float   _green;
        float   _blue;

    public:
        Color3f() {}
        Color3f(float r, float g, float b) : _red(r), _green(g), _blue(b) {}
    };

    /**
     *  用4个float表示颜色
     *  内存分别为Red,Green,Blue,Alpha
     *  每个分量的理论范围为0-1，Alpha为0表示全透明，1表示不透明
     */
    struct Color4f
    {
        float   _red;
        float   _green;
        float   _blue;
        float   _alpha;

    public:
        Color4f() {}
        Color4f(Color3f &c):_red(c._red), _green(c._green), _blue(c._blue), _alpha(1.0f) {}
        Color4f(float r, float g, float b, float a = 1.0f) : _red(r), _green(g), _blue(b), _alpha(a) {}
    };

    inline Color3f alphaBlend(Color3f &bgcolor, Color4f &fcolor)
    {
        float pA = 1.0f - fcolor._alpha;
        Color3f out;
        out._red = pA * bgcolor._red + fcolor._alpha * fcolor._red;
        out._green = pA * bgcolor._green + fcolor._alpha * fcolor._green;
        out._blue = pA * bgcolor._blue + fcolor._alpha * fcolor._blue;
        return out;
    }

    /**
     *  用四字节保存的颜色结构
     *  内存分别为Alpha,Blue,Green,Red
     *  可以用int值表示，形如0xAABBGGRR,其中Alpha为0不透明，255为全透明
     */
    union Color4b {
        int     _value;
        struct
        {
            byte    _alpha;
            byte    _blue;
            byte    _green;
            byte    _red;
        };

    public:
        Color4b() {}
        Color4b(int value) : _value(value) {}
        Color4b(byte a, byte r, byte g, byte b) : _alpha(a), _blue(b), _green(g), _red(r) {}
    };



    typedef struct Color3f          color3f;
    typedef struct Color4f          color4f;
    typedef union Color4b           color4b;
}

#pragma pack(pop)

#endif