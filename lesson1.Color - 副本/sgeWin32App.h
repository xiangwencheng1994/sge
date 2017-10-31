//////////////////////////////////////////////////////////////////////////
// sgeWin32Window.h
// Windows平台应用程序接口
//////////////////////////////////////////////////////////////////////////

#ifndef SGE_WIN32APP_H
#define SGE_WIN32APP_H

#include "sgeApp.h"
#include <Windows.h>

namespace sge
{
    class Win32App : public IApp
    {
    public:
        Win32App(int width, int height);
        ~Win32App();

        inline int width() { return _width; }
        inline int height() { return _height; }

        virtual int     exec();
    protected:
        virtual void    onRender(ICanvas *canvas)  =   0;
        virtual void    onResize(int width, int height);
        virtual HWND    onCreateWND();

        virtual LRESULT wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam);
        friend LRESULT CALLBACK winAppWndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam);

        int         _width;
        int         _height;
        HWND        _hWnd;
        HDC         _hDC;
        ICanvas*    _canvas;
        HDC         _hMem;
        void*       _buffer;
        HBITMAP     _surface;
    };
}

#endif //!SGE_WIN32APP_H