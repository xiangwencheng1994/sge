#pragma once

#include "sgeMath.h"

namespace sge
{
    class sgeTexture
    {
    public:
        sgeTexture(const char* file);
        ~sgeTexture();

        inline const color4b&  pixelAt(int x, int y) const { return _data[(y % _height) * _width + (x % _width)]; }

        inline int  width() const { return _width; }
        inline int  height() const { return _height; }

        const color4b   pixelUV(float u, float v) const;

    private:
        color4b*    _data;
        int         _width;
        int         _height;
    };

}


