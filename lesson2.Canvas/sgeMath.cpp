#include "sgeMath.h"

using namespace sge;

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