//////////////////////////////////////////////////////////////////////////
// Canvas.h
// 封装画布和绘图API
//////////////////////////////////////////////////////////////////////////

#ifndef SGE_CANVAS_H
#define SGE_CANVAS_H

#include "sgeMath.h"
#include "sgeTexture.h"

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
        void    drawPoint(int x, int y, const color4b& color);
        void    drawPointF(float x, float y, const color4b& color) { drawPoint(x * _width, y * _height, color); }
        void    drawLine(int x1, int y1, int x2, int y2, const color4b& c1);
        void    drawLineF(float x1, float y1, float x2, float y2, const color4b& c1) { drawLine(x1 * _width, y1 * _height, x2 * _width, y2 * _height,  c1); }
        void    drawLine(int x1, int y1, int x2, int y2, const color4b& c1, const color4b& c2);
        void    drawLineF(float x1, float y1, float x2, float y2, const color4b& c1, const color4b& c2) { drawLine(x1 * _width, y1 * _height, x2 * _width, y2 * _height, c1, c2); }

        void    drawTriangle(const Point& p1, const Point& p2, const Point& p3, const color4b& c1);
        void    drawTriangle(const Point& p1, const Point& p2, const Point& p3, const color4b& c1, const color4b& c2, const color4b& c3);

        void    drawTriangle(const xyuv& v1, const xyuv& v2, const xyuv& v3, const sgeTexture& tex);

        void    drawImage(int x, int y, const sgeTexture& tex);
        void    writeToBitmap(void* buffer, int width, int height) { memcpy(buffer, _pixels, dataSize()); }
    protected:
        void    drawSpanLine(int minX, int maxX, int y, const color4b& c1);
        void    drawSpanLine(int minX, int maxX, int y, const color4b& c1, const color4b& c2);
        void    drawFlatBottomTriangle(const Point& top, const Point& left, const Point& right, const color4b& c1);
        void    drawFlatBottomTriangle(const Point& top, const Point& left, const Point& right, const color4b& c1, const color4b& c2, const color4b& c3);
        void    drawFlatTopTriangle(const Point& bottom, const Point& left, const Point& right, const color4b& c1);
        void    drawFlatTopTriangle(const Point& bottom, const Point& left, const Point& right, const color4b& c1, const color4b& c2, const color4b& c3);

    private:
        int     dataSize() { return sizeof(color4b) * _width * _height; }
        color4b*            _pixels;
        int                 _width;
        int                 _height;
    };

}

#endif //!SGE_CANVAS_H