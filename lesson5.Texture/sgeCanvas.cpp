#include "sgeCanvas.h"
#include "sgeMath.h"

using namespace sge;

Canvas::Canvas(int width, int height)
    : _width(width), _height(height), _pixels(NULL)
{
    assert(width > 0 && height > 0);
    _pixels = (color4b*)malloc(dataSize());
}

Canvas::~Canvas()
{
    if (_pixels)
    {
        free(_pixels);
        _pixels = NULL;
    }
}

void Canvas::resize(int w, int h)
{
    _width = w;
    _height = h;
    _pixels = (color4b*)realloc(_pixels, dataSize());
}

void Canvas::clear()
{
    memset(_pixels, 0, dataSize());
}

void Canvas::drawPoint(int x, int y, const color4b& color)
{
    if (x < 0 || x >= _width || y < 0 || y >= _height) return;
    maskBlend(_pixels[y * _width + x], color);
}

void Canvas::drawLine(int x1, int y1, int x2, int y2, const color4b & c1)
{
    int x, y, dx, dy, s1, s2, p, temp, interchange, i;
    x = x1;
    y = y1;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    s1 = x2 > x1 ? 1 : -1;
    s2 = y2 > y1 ? 1 : -1;

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
    for (i = 1; i <= dx; ++i)
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

void Canvas::drawLine(int x1, int y1, int x2, int y2, const color4b & c1, const color4b & c2)
{
    int x, y, dx, dy, s1, s2, p, temp, interchange, i;
    x = x1;
    y = y1;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    
    s1 = x2 > x1 ? 1 : -1;
    s2 = y2 > y1 ? 1 : -1;

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
    for (i = 1; i <= dx; ++i)
    {
        drawPoint(x, y, colorLerp(c1, c2, (float)i / dx));
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

void Canvas::drawTriangle(const Point & p1, const Point & p2, const Point & p3, const color4b & c1)
{
    Point p[3] = { p1, p2, p3 };
    // sort by y
    if (p[1].y > p[0].y) Swap(p[0], p[1]);
    if (p[2].y > p[0].y) Swap(p[0], p[2]);
    if (p[1].y < p[2].y) Swap(p[1], p[2]);

    int px = (int)roundf(float(p[1].y - p[0].y) / (p[2].y - p[0].y) * (p[2].x - p[0].x) + p[0].x);
    Point mid(px, p[1].y);

    drawFlatBottomTriangle(p[0], p[1], mid, c1);
    drawFlatTopTriangle(p[2], p[1], mid, c1);
}

void Canvas::drawTriangle(const Point & p1, const Point & p2, const Point & p3, const color4b & c1, const color4b & c2, const color4b & c3)
{
    Point p[3] = { p1, p2, p3 };
    color4b c[3] = { c1, c2, c3 };
    // sort by y
    if (p[1].y > p[0].y) { Swap(p[0], p[1]); Swap(c[0], c[1]); }
    if (p[2].y > p[0].y) { Swap(p[0], p[2]); Swap(c[0], c[2]); }
    if (p[1].y < p[2].y) { Swap(p[1], p[2]); Swap(c[1], c[2]); }

    int px = (int)roundf(float(p[1].y - p[0].y) / (p[2].y - p[0].y) * (p[2].x - p[0].x) + p[0].x);
    Point mid(px, p[1].y);
    color4b cm = colorLerp(c[0], c[2], (float)(p[0].y - p[1].y) / (p[0].y - p[2].y));

    drawFlatBottomTriangle(p[0], p[1], mid, c[0], c[1], cm);
    drawFlatTopTriangle(p[2], p[1], mid, c[2], c[1], cm);
}

void Canvas::drawTriangle(const xyuv & v1, const xyuv & v2, const xyuv & v3, const sgeTexture & tex)
{
    int x1 = v1.x * _width, x2 = v2.x * _width, x3 = v3.x * _width;
    int y1 = v1.y * _height, y2 = v2.y * _height, y3 = v3.y * _height;
    aabb2i box(x1, y1);
    box.update(x2, y2);
    box.update(x3, y3);

    int dx23 = x2 - x3, dx31 = x3 - x1, dx12 = x1 - x2;
    int dy23 = y2 - y3, dy31 = y3 - y1, dy12 = y1 - y2;
    
    int ss =  dy23 * dx31 - dy31 * dx23;

    if (ss == 0) return; // 三个点在一条直线上

    for (int x = box.minX; x <= box.maxX; ++x)
    {
        if (x < 0) continue;
        if (x >= _width) break;
        for (int y = box.minY; y <= box.maxY; ++y)
        {
            if (y < 0) continue;
            if (y >= _height) break;

            int s1 = (y - y3) * dx23 + (x3 - x) * dy23;
            int s2 = (y - y1) * dx31 + (x1 - x) * dy31;
            int s3 = (y - y2) * dx12 + (x2 - x) * dy12;
            if ((s1 >= 0 && s2 >= 0 && s3 >= 0)
                || (s1 <= 0 && s2 <= 0 && s3 <= 0))
            {
                float b1 = (float)s1 / ss, b2 = (float)s2 / ss, b3 = (float)s3 / ss;
                float fu = b1 * v1.u + b2 * v2.u + b3 * v3.u;
                float fv = b1 * v1.v + b2 * v2.v + b3 * v3.v;
                maskBlend(_pixels[y * _width + x], tex.pixelUV(fu, fv));
            }
        }
    }
}

void Canvas::drawImage(int x, int y, const sgeTexture & tex)
{
    int imgWidth = tex.width(), imgHeight = tex.height();
    for (int sx = 0; sx < imgWidth; sx++)
    {
        int dx = x + sx;
        if (dx < 0 || dx >= _width) continue;
        for (int sy = 0; sy < imgHeight; sy++)
        {
            int dy = y - sy;
            if (dy < 0 || dy >= _height) continue;
            maskBlend(_pixels[dy * _width + dx], tex.pixelAt(sx, sy));
        }
    }
}

void Canvas::drawSpanLine(int minX, int maxX, int y, const color4b & c1)
{
    if (y < 0 || y >= _height) return;
    if (maxX >= _width) maxX = _width - 1;
    
    for (int x = minX < 0 ? 0 : minX; x <= maxX; ++x)
    {
        maskBlend(_pixels[y * _width + x], c1);
    }
}

void Canvas::drawSpanLine(int minX, int maxX, int y, const color4b & c1, const color4b & c2)
{
    if (y < 0 || y >= _height) return;
    int dx = maxX - minX;
    if (maxX >= _width) maxX = _width - 1;

    for (int x = minX < 0 ? 0 : minX; x <= maxX; ++x)
    {
        maskBlend(_pixels[y * _width + x], colorLerp(c1, c2, (float)(x - minX) / dx));
    }
}

void Canvas::drawFlatBottomTriangle(const Point& top, const Point& left, const Point& right, const color4b& c1)
{
    float dy = top.y - left.y;
    float stepX1 = (top.x - left.x) / dy;
    float stepX2 = (top.x - right.x) / dy;
    float leftX = top.x;
    float rightX = top.x;
    for (int y = top.y; y >= left.y; --y)
    {
        if (rightX > leftX) drawSpanLine((int)roundf(leftX), (int)roundf(rightX), y, c1);
        else drawSpanLine((int)roundf(rightX), (int)roundf(leftX), y, c1);
        leftX -= stepX1;
        rightX -= stepX2;
    }
}

void Canvas::drawFlatBottomTriangle(const Point & top, const Point & left, const Point & right, const color4b & c1, const color4b & c2, const color4b& c3)
{
    float dy = top.y - left.y;
    float stepX1 = (top.x - left.x) / dy;
    float stepX2 = (top.x - right.x) / dy;
    float leftX = top.x;
    float rightX = top.x;
    float dlr = (c1._red - c2._red) / dy;
    float dlg = (c1._green - c2._green) / dy;
    float dlb = (c1._blue - c2._blue) / dy;
    float dla = (c1._alpha - c2._alpha) / dy;
    float drr = (c1._red - c3._red) / dy;
    float drg = (c1._green - c3._green) / dy;
    float drb = (c1._blue - c3._blue) / dy;
    float dra = (c1._alpha - c3._alpha) / dy;
    float lr = c1._red, lg = c1._green, lb = c1._blue, la = c1._alpha;
    float rr = c1._red, rg = c1._green, rb = c1._blue, ra = c1._alpha;
    for (int y = top.y; y >= left.y; --y)
    {
        if (rightX > leftX) drawSpanLine((int)roundf(leftX), (int)roundf(rightX), y, color4b(la, lr, lg, lb), color4b(ra, rr, rg, rb));
        else drawSpanLine((int)roundf(rightX), (int)roundf(leftX), y, color4b(ra, rr, rg, rb), color4b(la, lr, lg, lb));
        leftX -= stepX1;
        rightX -= stepX2;
        lr -= dlr; lg -= dlg; lb -= dlb; la -= dla;
        rr -= drr; rg -= drg; rb -= drb; ra -= dra;
    }
}


void Canvas::drawFlatTopTriangle(const Point& bottom, const Point& left, const Point& right, const color4b& c1)
{
    float dy = right.y - bottom.y;
    float stepX1 = (bottom.x - left.x) / dy;
    float stepX2 = (bottom.x - right.x) / dy;
    float leftX = bottom.x;
    float rightX = bottom.x;
    for (int y = bottom.y; y < right.y; ++y)
    {
        if (rightX > leftX) drawSpanLine((int)roundf(leftX), (int)roundf(rightX), y, c1);
        else drawSpanLine((int)roundf(rightX), (int)roundf(leftX), y, c1);
        leftX -= stepX1;
        rightX -= stepX2;
    }
}

void Canvas::drawFlatTopTriangle(const Point & bottom, const Point & left, const Point & right, const color4b & c1, const color4b & c2, const color4b & c3)
{
    float dy = right.y - bottom.y;
    float stepX1 = (bottom.x - left.x) / dy;
    float stepX2 = (bottom.x - right.x) / dy;
    float leftX = bottom.x;
    float rightX = bottom.x;
    float dlr = (c1._red - c2._red) / dy;
    float dlg = (c1._green - c2._green) / dy;
    float dlb = (c1._blue - c2._blue) / dy;
    float dla = (c1._alpha - c2._alpha) / dy;
    float drr = (c1._red - c3._red) / dy;
    float drg = (c1._green - c3._green) / dy;
    float drb = (c1._blue - c3._blue) / dy;
    float dra = (c1._alpha - c3._alpha) / dy;
    float lr = c1._red, lg = c1._green, lb = c1._blue, la = c1._alpha;
    float rr = c1._red, rg = c1._green, rb = c1._blue, ra = c1._alpha;
    for (int y = bottom.y; y < right.y; ++y)
    {
        if (rightX > leftX) drawSpanLine((int)roundf(leftX), (int)roundf(rightX), y, color4b(la, lr, lg, lb), color4b(ra, rr, rg, rb));
        else drawSpanLine((int)roundf(rightX), (int)roundf(leftX), y, color4b(ra, rr, rg, rb), color4b(la, lr, lg, lb));
        leftX -= stepX1;
        rightX -= stepX2;
        lr -= dlr; lg -= dlg; lb -= dlb; la -= dla;
        rr -= drr; rg -= drg; rb -= drb; ra -= dra;
    }
}
