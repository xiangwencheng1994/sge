//////////////////////////////////////////////////////////////////////////
// sgeApp.h
// 封装Windows平台窗口
//////////////////////////////////////////////////////////////////////////

#ifndef SGE_WIN32APP_H
#define SGE_WIN32APP_H

#include <Windows.h>

namespace sge
{
    class Canvas;

    class sgeApp
    {
    public:
        static sgeApp* instance;

    public:
        sgeApp(int width, int height);
        ~sgeApp();

        int width() { return _width; }
        int height() { return _height; }

        virtual int     exec();

        virtual LRESULT wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam);

    protected:
        virtual void    onRender(Canvas *canvas) = 0;
        virtual void    onResize(int width, int height);
        virtual HWND    onCreateWND();

        int         _width;
        int         _height;
        HWND        _hWnd;
        HDC         _hDC;
        Canvas*     _canvas;
        HDC         _hMem;
        void*       _buffer;
        HBITMAP     _surface;
    };

}

#endif //!SGE_WIN32APP_H