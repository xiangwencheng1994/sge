//////////////////////////////////////////////////////////////////////////
//  sgeMath.h
//  用于定义一些常用数学结构和函数
//////////////////////////////////////////////////////////////////////////
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

    template<typename T> void Swap(T& a, T& b) { T temp = a; a = b; b = temp; }
    inline float Sin(float x) { return sinf(x); }
    inline float Cos(float x) { return cosf(x); }
    inline float Tan(float x) { return tanf(x); }
    inline float Asin(float x) { return asinf(x); }
    inline float Acos(float x) { return acosf(x); }
    inline float Atan(float x) { return atanf(x); }
    inline float Atan2(float x, float y) { return atan2f(x, y); }
    inline float Sqrt(float x) { float sqrtf(x); }
    inline float Fabs(float x) { float fabs(x); }
    inline double Sin(double x) { return sin(x); }
    inline double Cos(double x) { return cos(x); }
    inline double Tan(double x) { return tan(x); }
    inline double Asin(double x) { return asin(x); }
    inline double Acos(double x) { return acos(x); }
    inline double Atan(double x) { return atan(x); }
    inline double Atan2(double x, double y) { return atan2(x, y); }
    inline double Sqrt(double x) { return sqrt(x); }
    inline double Fabs(double x) { return fabs(x); }
    template<typename T> inline void SinCos(T _X, T *_S, T *_C) { *_S = Sin(_X); *_C = Cos(_X); }

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
     *  用四字节保存的颜色结构
     *  内存分别为Blue,Green,Red,Alpha，当Alpha为0时与位图保持一致
     *  与int互转，形如0xAARRGGBB,其中Alpha为0不透明，255为全透明
     */
    struct Color4b {
        byte    _blue;
        byte    _green;
        byte    _red;
        byte    _alpha;

    public:
        Color4b() {}
        Color4b(int value) { _blue = value; _green = value >> 8; _red = value >> 16; _alpha = value >> 24; }
        Color4b(byte a, byte r, byte g, byte b) : _alpha(a), _blue(b), _green(g), _red(r) {}
        friend  bool    operator == (const Color4b& left, const Color4b& right)
        {
            return  left._red == right._red &&
                left._green == right._green &&
                left._blue == right._blue &&
                left._alpha == right._alpha;
        }
        friend  bool    operator != (const Color4b& left, const Color4b& right)
        {
            return  left._red != right._red ||
                left._green != right._green ||
                left._blue != right._blue ||
                left._alpha != right._alpha;
        }
        operator unsigned()
        {
            unsigned    color;
            char*       pColor = (char*)&color;
            pColor[0] = _red;
            pColor[1] = _green;
            pColor[2] = _blue;
            pColor[3] = _alpha;
            return  color;
        }
        operator int()
        {
            int         color;
            char*       pColor = (char*)&color;
            pColor[0] = _red;
            pColor[1] = _green;
            pColor[2] = _blue;
            pColor[3] = _alpha;
            return  color;
        }
        unsigned int toInt() { return  (_blue) | (_green << 8) | (_red << 16) | (_alpha << 24); }
        Color4b     operator +(const Color4b& c) const { return Color4b(_alpha + c._alpha, _red + c._red, _green + c._green, _blue + c._blue); }
        Color4b     operator -(const Color4b& c) const { return Color4b(_alpha - c._alpha, _red - c._red, _green - c._green, _blue - c._blue); }
        Color4b&    operator +=(const Color4b& c) { _red += c._red, _green += c._green, _blue += c._blue, _alpha += c._alpha; return *this; }
        Color4b&    operator -=(const Color4b& c) { _red -= c._red, _green -= c._green, _blue -= c._blue, _alpha -= c._alpha; return *this; }
        Color4b     operator *(float k) const { return Color4b(_alpha * k, _red * k, _green * k, _blue * k); }
        Color4b     operator /(float k) const { return Color4b(_alpha / k, _red / k, _green / k, _blue / k); }
        Color4b&    operator *=(float k) { _red *= k, _green *= k, _blue *= k, _alpha *= k; return *this; }
        Color4b&    operator /=(float k) { _red /= k, _green /= k, _blue /= k, _alpha /= k; return *this; }
    };

    /**
     *  颜色插值
     */
    Color3f   colorLerp(const Color3f& c1, const Color3f& c2, float s);

    /**
     *  颜色插值
     */
    Color4f   colorLerp(const Color4f& c1, const Color4f& c2, float s);

    /**
     *  颜色插值
     */
    Color4b   colorLerp(const Color4b& c1, const Color4b& c2, float s);

    /**
     *  不透明颜色和半透明颜色的混合
     *  假设一幅图象是A，另一幅透明的图象是B，那么透过B去看A，返回最终看到的颜色
     */
    Color3f alphaBlend(const Color3f &bgcolor, const Color4f &fcolor);

    /**
     *  半透明颜色和半透明颜色的混合
     *  求两块半透明颜色的玻璃重叠后的颜色及透明度
     */
    Color4f alphaBlend(const Color4f &c1, const Color4f &c2);

    /**
     *  不透明颜色上叠加半透明颜色
     */
    void    maskBlend(Color4b &bgColor, const Color4b& fontColor);

    typedef struct Color3f          color3f;
    typedef struct Color4f          color4f;
    typedef struct Color4b          color4b;
     

    // Vector2<T>
    // 2d 向量
    template<typename T>
    class Vector2
    {
    public:
        T  x;
        T  y;

    public:
        Vector2() {}
        Vector2(const Vector2<T> &a) : x(a.x), y(a.y) {}
        Vector2(T x, T y) : x(x), y(y) {}

        inline Vector2<T>&  operator =  (const Vector2<T> &b) { x = b.x, y = b.y; return *this; }
        inline bool         operator == (const Vector2<T> &b) const { return x == b.x && y == b.y; }
        inline bool         operator != (const Vector2<T> &b) const { return x != b.x || y != b.y; }

        inline Vector2<T>   operator -  () const { return Vector2<T>(-x, -y); }

        inline Vector2<T>   operator +  (const Vector2<T> &b) const { return Vector2<T>(x + b.x, y + b.y); }
        inline Vector2<T>   operator -  (const Vector2<T> &b) const { return Vector2<T>(x - b.x, y - b.y); }
        inline Vector2<T>   operator += (const Vector2<T> &b) { x += b.x; y += b.y; return *this; }
        inline Vector2<T>   operator -= (const Vector2<T> &b) { x -= b.x; y -= b.y; return *this; }

        inline Vector2<T>   operator *  (T b) const { return Vector2<T>(x * b, y * b); }
        friend Vector2<T>   operator *  (T a, const Vector2<T> &b) { return Vector2<T>(a * b.x, a * b.y); }
        inline Vector2<T>   operator /  (T b) const { return Vector2<T>(x / b, y / b); }
        friend Vector2<T>   operator /  (T a, const Vector2<T> &b) { return Vector2<T>(a / b.x, a / b.y); }
        inline Vector2<T>   operator *= (T b) { x *= b; y *= b; return *this; }
        inline Vector2<T>   operator /= (T b) { x /= b; y /= b; return *this; }

        // 点乘
        friend inline T     Dot(const Vector2<T> &a, const Vector2<T> &b) { return a * b; }
        inline T            operator *  (const Vector2<T> &b) const { return x * b.x + y * b.y; }

        // 置零
        inline void zero() { x = y = 0; }
        // 模长
        inline T    length() const { return (T)Sqrt(x * x + y * y); }
        // 单位化向量
        void normalize() 
        {
            T magSq = x * x + y * y;
            if (magSq > (T)0)
            {
                T oneOverMag = (T)(1 / (T)Sqrt(magSq));
                x *= oneOverMag;
                y *= oneOverMag;
            }
        }
    };



    typedef class Vector2<int>      Point;
    typedef class Vector2<int>      vec2i;
    typedef class Vector2<float>    vec2f;
    typedef class Vector2<double>   vec2d;

}

#pragma pack(pop)

#endif