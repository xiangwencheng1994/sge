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
        color4f red(1, 0, 0);
        for (int i = 0; i < 100; ++i)
        {
            int x = i * 10;
            int y = i * 10;
            _canvas->drawPoint(x, y, red);
        }
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