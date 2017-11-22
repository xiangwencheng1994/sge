#include <Windows.h>

#include "sgeApp.h"
#include "sgeCanvas.h"

using namespace sge;

class MyApp : public sgeApp
{
public:
    sgeTexture  texture;
    xyuv      p1;
    xyuv      p2;
    xyuv      p3;
    xyuv      p4;

    MyApp(int w, int h) : sgeApp(w, h), texture("D://tex.jpg")
    {
        p1 = xyuv(0.2f, 0.2, 0, 1);
        p2 = xyuv(0.8, 0.2, 1, 1);
        p3 = xyuv(0.5, 0.8, 0, 0);
    }

protected:
    virtual void    onRender(Canvas* _canvas)
    {
        _canvas->clear();
        _canvas->drawTriangle(p1, p2, p3, texture);
    }
};

int WINAPI WinMain(HINSTANCE hInst,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{
    MyApp app(640,480);
    app.exec();
    return 0;
}