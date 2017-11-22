#include "sgeTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace sge;

sgeTexture::sgeTexture(const char * file)
    : _width(0), _height(0), _data(NULL)
{
    assert(file);
    int comp = 0;
    byte* data = stbi_load(file, &_width, &_height, &comp, 4);
    assert(data && "stbi_load failed, see stbi_failure_reason()");
    for (int y = 0; y < _height; ++y)
    {
        int dy = y * _width;
        for (int x = 0; x < _width; ++x)
        {
            // rgba ==> bgra
            Swap(data[(dy + x) * 4 + 0], data[(dy + x) * 4 + 2]);
        }
    }
    _data = (color4b*)data;
}

sgeTexture::~sgeTexture()
{
    if (_data)
    {
        stbi_image_free(_data);
        _data = NULL;
    }
}

const color4b sge::sgeTexture::pixelUV(float u, float v) const
{
    float x = u * _width;
    float y = v * _height;

    return  pixelAt(x, y);
}
