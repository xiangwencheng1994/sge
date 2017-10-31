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

#define PI              (3.14159265358979323846)
#define DEG2RAD(x)      (x * PI / 180)      // 角度转弧度
#define RAD2EDG(x)      (x * 180 / PI)      // 弧度转角度

namespace sge
{
    typedef unsigned char       byte;
    typedef int                 sizei;
    typedef struct Color4f       Color4f;

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
     *  每个分量的理论范围为0-1
     */
    struct Color4f
    {
        float   _red;
        float   _green;
        float   _blue;
        float   _alpha;

    public:
        Color4f() {}
        Color4f(Color3f &c):_red(c._red), _green(c._green), _blue(c._blue), _alpha(0) {}
        Color4f(float r, float g, float b, float a = 0) : _red(r), _green(g), _blue(b), _alpha(a) {}
    };

    /**
     *  用四字节保存的颜色结构
     *  内存分别为Alpha,Blue,Green,Red
     *  可以用int值表示，形如0xAABBGGRR
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
        Color4b(int value) : _value(value) {}
        Color4b(byte a, byte r, byte g, byte b) : _alpha(a), _blue(b), _green(g), _red(r) {}
    };

}

#pragma pack(pop)

#endif