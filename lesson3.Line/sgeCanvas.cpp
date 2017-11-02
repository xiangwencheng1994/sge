#include "sgeCanvas.h"
#include "sgeMath.h"

using namespace sge;

Canvas::Canvas(int width, int height)
    : _width(width), _height(height), _pixels(NULL)
{
    assert(width > 0 && height > 0);
    _pixels = (color3f*)malloc(dataSize());
}

Canvas::~Canvas()
{
    if (_pixels)
    {
        free(_pixels);
        _pixels = NULL;
    }
}

void sge::Canvas::resize(int w, int h)
{
    _width = w;
    _height = h;
    _pixels = (color3f*)realloc(_pixels, dataSize());
}

void sge::Canvas::clear()
{
    memset(_pixels, 0, dataSize());
}

void sge::Canvas::drawPoint(int x, int y, const color4f& color)
{
    if (x < 0 || x >= _width || y < 0 || y >= _height) return;
    Color3f & bkcolor = _pixels[y * _width + x];
    bkcolor = alphaBlend(bkcolor, color);
}

void sge::Canvas::drawLine(int x1, int y1, int x2, int y2, const color4f & c1)
{
    int x, y, dx, dy, s1, s2, p, temp, interchange, i;
    x = x1;
    y = y1;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    if (x2 > x1)
        s1 = 1;
    else
        s1 = -1;

    if (y2 > y1)
        s2 = 1;
    else
        s2 = -1;

    if (dy > dx)
    {
        temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    }
    else
        interchange = 0;

    p = 2 * dy - dx;
    int pIndexMax = _width * _height;
    for (i = 1; i <= dx; i++)
    {
        drawPoint(x, y, c1);
        if (p >= 0)
        {
            if (interchange == 0)
                y = y + s2;
            else
                x = x + s1;
            p = p - 2 * dx;
        }
        if (interchange == 0)
            x = x + s1;
        else
            y = y + s2;
        p = p + 2 * dy;
    }
}

void sge::Canvas::drawLine(int x1, int y1, int x2, int y2, const color4f & c1, const color4f & c2)
{
    int x, y, dx, dy, s1, s2, p, temp, interchange, i;
    Color4f stepColor = c2 - c1;
    Color4f color = c1;
    x = x1;
    y = y1;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    
    if (x2 > x1)
        s1 = 1;
    else
        s1 = -1;

    if (y2 > y1)
        s2 = 1;
    else
        s2 = -1;

    if (dy > dx)
    {
        temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    }
    else
    {
        interchange = 0;
    }

    p = 2 * dy - dx;
    stepColor /= (float)dx;
    for (i = 1; i <= dx; i++)
    {
        drawPoint(x, y, color);
        if (p >= 0)
        {
            if (interchange == 0)
                y = y + s2;
            else
                x = x + s1;
            p = p - 2 * dx;
        }
        if (interchange == 0)
            x = x + s1;
        else
            y = y + s2;
        p = p + 2 * dy;

        color += stepColor;
    }
}

void sge::Canvas::writeToBitmap(void* buffer,int width, int height, int startX, int startY)
{
    typedef struct _tagRGBQUAD // BITMAP的颜色结构
    {
        byte  rgbBlue;
        byte  rgbGreen;
        byte  rgbRed;
        byte  rgbReserved;
    } RGBQUAD;

    RGBQUAD* pBuff = (RGBQUAD*)buffer; 
    for (int y = startY; y < height; ++y)
    {
        int dstdp = y * width;
        int srcdp = y * _width;
        for (int x = startX; x < width; ++x)
        {
            RGBQUAD& dst = pBuff[dstdp + x];
            Color3f& src = _pixels[srcdp + x];
            dst.rgbBlue = (byte)roundf(src._blue * 255.0f);
            dst.rgbGreen = (byte)roundf(src._green * 255.0f);
            dst.rgbRed = (byte)roundf(src._red * 255.0f);
            dst.rgbReserved = 0;
        }
    }
}