#include <Windows.h>

#include "sgeApp.h"
#include "sgeCanvas.h"

using namespace sge;

class MyApp : public sgeApp
{
public:
    MyApp(int w, int h) : sgeApp(w, h) {}

protected:
    virtual void    onRender(Canvas* _canvas)
    {
        _canvas->clear();
        Point p1(300, 400);
        Point p2(100, 150);
        Point p3(600, 50);
        _canvas->drawTriangle(p1, p2, p3, 0xFFFF0000, 0xFF00FF00, 0xFF0000FF);
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