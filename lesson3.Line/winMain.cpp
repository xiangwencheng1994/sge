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
        int margin = 50;
        int mx = _canvas->width() - margin;
        int my = _canvas->height() - margin;
        _canvas->drawLine(margin, margin, mx, margin, color4f(1, 0, 0));
        _canvas->drawLine(mx, margin, mx, my, color4f(0, 1, 0), color4f(0, 0, 1));
        _canvas->drawLine(mx, my, margin, my, color4f(0, 1, 1), color4f(1, 1, 0));
        _canvas->drawLine(margin, my, margin, margin, color4f(1, 0, 1), color4f(1, 0, 0));

        _canvas->drawLine(margin, margin, mx, my, color4f(1, 0, 0), color4f(0,1,0));
        _canvas->drawLine(margin, my, mx, margin, color4f(0, 0, 1), color4f(0, 1, 0));

        _canvas->drawLine(100, 100, 400, 400, color4f(1, 1, 1));
        _canvas->drawLine(100, 100, 300, 300, color4f(1, 0, 0, 0.8f));
        _canvas->drawLine(200, 200, 400, 400, color4f(0, 1, 0, 0.6f));
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