#include "sgeMath.h"

using namespace sge;


Color3f sge::colorLerp(const Color3f & c1, const Color3f & c2, float s)
{
    Color3f   color;
    color._red = (c1._red + s * (c2._red - c1._red));
    color._green = (c1._green + s * (c2._green - c1._green));
    color._blue = (c1._blue + s * (c2._blue - c1._blue));
    return color;
}

Color4f sge::colorLerp(const Color4f & c1, const Color4f & c2, float s)
{
    Color4f   color;
    color._red = (c1._red + s * (c2._red - c1._red));
    color._green = (c1._green + s * (c2._green - c1._green));
    color._blue = (c1._blue + s * (c2._blue - c1._blue));
    color._alpha = (c1._alpha + s * (c2._alpha - c1._alpha));
    return color;
}

Color4b sge::colorLerp(const Color4b & c1, const Color4b & c2, float s)
{
    Color4b   color;
    color._red = (byte)(c1._red + s * (c2._red - c1._red));
    color._green = (byte)(c1._green + s * (c2._green - c1._green));
    color._blue = (byte)(c1._blue + s * (c2._blue - c1._blue));
    color._alpha = (byte)(c1._alpha + s * (c2._alpha - c1._alpha));
    return color;
}

Color3f sge::alphaBlend(const Color3f &bgcolor, const Color4f &fcolor)
{
    float pA = 1.0f - fcolor._alpha;
    Color3f out;
    out._red = pA * bgcolor._red + fcolor._alpha * fcolor._red;
    out._green = pA * bgcolor._green + fcolor._alpha * fcolor._green;
    out._blue = pA * bgcolor._blue + fcolor._alpha * fcolor._blue;
    return out;
}

Color4f sge::alphaBlend(const Color4f &c1, const Color4f &c2)
{
    Color4f out;
    out._alpha = c1._alpha + c2._alpha - c1._alpha * c2._alpha;
    float k = (1.0f - c2._alpha) * c1._alpha;
    out._red = (k * c1._red + c2._alpha * c2._red) / out._alpha;
    out._green = (k * c1._green + c2._alpha * c2._green) / out._alpha;
    out._blue = (k * c1._blue + c2._alpha * c2._blue) / out._alpha;
    return out;
}

void sge::maskBlend(Color4b & bgColor, const Color4b & fontColor)
{
    bgColor._blue = ((255 - fontColor._alpha) * bgColor._blue + fontColor._alpha * fontColor._blue) >> 8;
    bgColor._green = ((255 - fontColor._alpha) * bgColor._green + fontColor._alpha * fontColor._green) >> 8;
    bgColor._red = ((255 - fontColor._alpha) * bgColor._red + fontColor._alpha * fontColor._red) >> 8;
    bgColor._alpha = 0;
}
