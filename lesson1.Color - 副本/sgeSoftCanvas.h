
#ifndef SGE_SOFT_CANVAS_H
#define SGE_SOFT_CANVAS_H

#include "sgeCanvas.h"

namespace sge
{
    /**
     *  采用软件渲染的画布
     */
    class SoftCanvas : public ICanvas
    {
    public:
        SoftCanvas(int width, int height);
        ~SoftCanvas();

        int     width() { return _width; }
        int     height() { return _height; }
        void    resize(int w, int h);

        void    clear();
        void    drawPoint(float x, float y, Color4f color);

        void    writeToBitmap(void* buffer, int width, int height, int startX = 0, int startY = 0);
    protected:
        void        blendPixelColor(int x, int y, Color4f color);
        Color4f&    pixel(int x, int y) { return _pixels[y * _width + x]; }
        
    private:

        Color4f*            _pixels;
        int                 _width;
        int                 _height;
        float               _halfWidth;
        float               _halfHeight;
        float               _pixelWidth;
        float               _pixelHeight;
    };

}

#endif //!SGE_SOFT_CANVAS_H


