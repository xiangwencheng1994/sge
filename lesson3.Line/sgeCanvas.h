//////////////////////////////////////////////////////////////////////////
// Canvas.h
// 封装画布和绘图API
//////////////////////////////////////////////////////////////////////////

#ifndef SGE_CANVAS_H
#define SGE_CANVAS_H

#include "sgeMath.h"

namespace sge
{
    /**
     *  画布
     */
    class Canvas
    {
    public:
        Canvas(int width, int height);
        ~Canvas();

        int     width() { return _width; }
        int     height() { return _height; }
        void    resize(int w, int h);

        void    clear();
        void    drawPoint(int x, int y, const color4f& color);
        void    drawLine(int x1, int y1, int x2, int y2, const color4f& c1);
        void    drawLine(int x1, int y1, int x2, int y2, const color4f& c1, const color4f& c2);

        void    writeToBitmap(void* buffer, int width, int height, int startX = 0, int startY = 0);
    private:
        int     dataSize() { return sizeof(color3f) * _width * _height; }
        color3f*            _pixels;
        int                 _width;
        int                 _height;
    };

}

#endif //!SGE_CANVAS_H