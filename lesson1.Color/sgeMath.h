/**
 *  sgeMath.h
 *  用于定义一些常用数学结构和函数
 */
#ifndef SGE_MATH_H
#define SGE_MATH_H

#pragma pack(push)
#pragma pack(1)

namespace sge
{
    typedef unsigned char       byte;
    typedef int                 sizei;

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
        Color4b(int value) : _value(value) {}
        Color4b(byte a, byte r, byte g, byte b) : _alpha(a), _blue(b), _green(g), _red(r) {}
    };



    typedef struct Color4f      Color4f;
    typedef union Color4b       Color4b;
}

#pragma pack(pop)

#endif