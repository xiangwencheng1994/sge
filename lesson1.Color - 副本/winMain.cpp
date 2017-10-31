#include <Windows.h>

#include "sgeApp.h"
#include "sgeSoftCanvas.h"

using namespace sge;

class MyApp : public App
{
public:
    MyApp() : App(640, 480) {}

protected:
    virtual void    onRender(ICanvas* _canvas)
    {
        _canvas->clear();
        for (int i = 0; i < 1000; ++i)
        {
            float x = (rand() % 2000 - 1000) * 0.001f;
            float y = (rand() % 2000 - 1000) * 0.001f;
            float r = (rand() % 1000) * 0.001f;
            float g = (rand() % 1000) * 0.001f;
            float b = (rand() % 1000) * 0.001f;
            _canvas->drawPoint(x, y, Color4f(r, g, b, 0));
        }
    }
};

int WINAPI WinMain(HINSTANCE hInst,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{
    MyApp app;
    app.exec();
    return 0;
}