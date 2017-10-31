#include "sgeSoftCanvas.h"
#include "sgeMath.h"

using namespace sge;

SoftCanvas::SoftCanvas(int width, int height)
    : _width(width), _height(height), _pixels(NULL)
{
    assert(width > 0 && height > 0);
    _halfWidth = _width * 0.5f;
    _halfHeight = _height * 0.5f;
    _pixelWidth = 2.0f / _width;
    _pixelHeight = 2.0f / _height;
    _pixels = (Color4f*)malloc(sizeof(Color4f) * _width * _height);
}

SoftCanvas::~SoftCanvas()
{
    if (_pixels)
    {
        free(_pixels);
        _pixels = NULL;
    }
}

void sge::SoftCanvas::resize(int w, int h)
{
    _width = w;
    _height = h;
    _halfWidth = _width * 0.5f;
    _halfHeight = _height * 0.5f;
    _pixelWidth = 2.0f / _width;
    _pixelHeight = 2.0f / _height;
    _pixels = (Color4f*)realloc(_pixels, sizeof(Color4f) * _width * _height);
}

void sge::SoftCanvas::clear()
{
    memset(_pixels, 0, sizeof(Color4f) * _width * _height);
}

void sge::SoftCanvas::drawPoint(float x, float y, Color4f color)
{
    float pos_x = round((x + 1.0f) * _halfWidth);
    float pos_y = round((y + 1.0f) * _halfHeight);
    int pixel_x = (int)pos_x;
    int pixel_y = (int)pos_y;
    if (pixel_x < 0 || pixel_x >= _width || pixel_y < 0 || pixel_y >= _height) return;
    blendPixelColor(pixel_x, pixel_y, color);
}

void sge::SoftCanvas::writeToBitmap(void* buffer,int width, int height, int startX, int startY)
{
    typedef struct _tagRGBQUAD // BITMAP的颜色结构
    {
        byte  rgbBlue;
        byte  rgbGreen;
        byte  rgbRed;
        byte  rgbReserved;
    } RGBQUAD;

    RGBQUAD* pixels = (RGBQUAD*)buffer;
    for (int x = startX; x < width; ++x)
    {
        for (int y = startY; y < height; ++y)
        {
            RGBQUAD& dst = pixels[y * width + x];
            dst.rgbBlue = round(pixel(x, y)._blue * 255.0f);
            dst.rgbGreen = round(pixel(x, y)._green * 255.0f);
            dst.rgbRed = round(pixel(x, y)._red * 255.0f);
            dst.rgbReserved = 0;
        }
    }
}

void sge::SoftCanvas::blendPixelColor(int x, int y, Color4f color)
{
    Color4f& dstColor = pixel(x, y);
    float pA = 1.0f - color._alpha;
    dstColor._red = pA * color._red + color._alpha * dstColor._red;
    dstColor._green = pA * color._green + color._alpha * dstColor._green;
    dstColor._blue = pA * color._blue + color._alpha * dstColor._blue;
    dstColor._alpha = 0;
}