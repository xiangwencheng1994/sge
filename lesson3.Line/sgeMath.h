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
        Color3f(const Color3f& c) :_red(c._red), _green(c._green), _blue(c._blue) {}
        Color3f(float r, float g, float b) : _red(r), _green(g), _blue(b) {}

        Color3f     operator +(const Color3f& c) const { return Color3f(_red + c._red, _green + c._green, _blue + c._blue); }
        Color3f     operator -(const Color3f& c) const { return Color3f(_red - c._red, _green - c._green, _blue - c._blue); }
        Color3f&    operator +=(const Color3f& c) { _red += c._red, _green += c._green, _blue += c._blue; return *this; }
        Color3f&    operator -=(const Color3f& c) { _red -= c._red, _green -= c._green, _blue -= c._blue; return *this; }
        Color3f     operator *(float k) const { return Color3f(_red * k, _green * k, _blue * k); }
        Color3f     operator /(float k) const { return Color3f(_red / k, _green / k, _blue / k); }
        Color3f&    operator *=(float k) { _red *= k, _green *= k, _blue *= k; return *this; }
        Color3f&    operator /=(float k) { _red /= k, _green /= k, _blue /= k; return *this; }
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
        Color4f(const Color3f &c) :_red(c._red), _green(c._green), _blue(c._blue), _alpha(1.0f) {}
        Color4f(float r, float g, float b, float a = 1.0f) : _red(r), _green(g), _blue(b), _alpha(a) {}

        Color4f     operator +(const Color4f& c) const { return Color4f(_red + c._red, _green + c._green, _blue + c._blue, _alpha + c._alpha); }
        Color4f     operator -(const Color4f& c) const { return Color4f(_red - c._red, _green - c._green, _blue - c._blue, _alpha - c._alpha); }
        Color4f&    operator +=(const Color4f& c) { _red += c._red, _green += c._green, _blue += c._blue, _alpha += c._alpha; return *this; }
        Color4f&    operator -=(const Color4f& c) { _red -= c._red, _green -= c._green, _blue -= c._blue, _alpha -= c._alpha; return *this; }
        Color4f     operator *(float k) const { return Color4f(_red * k, _green * k, _blue * k, _alpha * k); }
        Color4f     operator /(float k) const { return Color4f(_red / k, _green / k, _blue / k, _alpha / k); }
        Color4f&    operator *=(float k) { _red *= k, _green *= k, _blue *= k, _alpha *= k; return *this; }
        Color4f&    operator /=(float k) { _red /= k, _green /= k, _blue /= k, _alpha /= k; return *this; }
    };

    /**
    *  不透明颜色和半透明颜色的混合
    *  假设一幅图象是A，另一幅透明的图象是B，那么透过B去看A，返回最终看到的颜色
    */
    Color3f alphaBlend(const Color3f &bgcolor, const Color4f &fcolor);

    /**
    *  半透明颜色和半透明颜色的混合
    *  求两块半透明颜色的玻璃重叠后的颜色及透明度
    */
    inline Color4f alphaBlend(const Color4f &c1, const Color4f &c2);

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
        Color4b(const Color4b& c) : _value(c._value) {}
        Color4b(int value) : _value(value) {}
        Color4b(byte a, byte r, byte g, byte b) : _alpha(a), _blue(b), _green(g), _red(r) {}
    };

    typedef struct Color3f          color3f;
    typedef struct Color4f          color4f;
    typedef union Color4b           color4b;
}

#pragma pack(pop)

#endif