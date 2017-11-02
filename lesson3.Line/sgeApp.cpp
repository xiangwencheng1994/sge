#include "sgeApp.h"
#include "sgeCanvas.h"

using namespace sge;

#define WNDCLASSNAME  TEXT("sgeWindow")

sgeApp* sgeApp::instance = NULL;

static LRESULT CALLBACK winAppWndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
{
    if (sgeApp::instance) // 分发到对应类的实现中去
        return sgeApp::instance->wndProc(hWnd, msgId, wParam, lParam);
    return DefWindowProc(hWnd, msgId, wParam, lParam);
}

static bool registerWinClass()
{
    static bool isRegistered = false;
    if (isRegistered) return true;
    WNDCLASSEX  wnd;
    memset(&wnd, 0, sizeof(wnd));
    wnd.cbSize = sizeof(wnd);
    wnd.lpfnWndProc = winAppWndProc;
    wnd.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    wnd.hCursor = LoadCursor(0, IDC_ARROW);
    wnd.hIcon = 0;
    wnd.hIconSm = 0;
    wnd.hInstance = 0;
    wnd.lpszClassName = WNDCLASSNAME;
    wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    isRegistered = RegisterClassEx(&wnd) ? true : false;
    return isRegistered;
}

sgeApp::sgeApp(int width, int height)
    : _width(width), _height(height), _hWnd(NULL),
    _canvas(NULL), _hDC(0), _hMem(0), _buffer(0), _surface(0)
{
    bool ret = registerWinClass();
    assert(ret);
    sgeApp::instance = this;
}

sgeApp::~sgeApp()
{
    UnregisterClass(WNDCLASSNAME, 0);
    if (_canvas)
    {
        delete _canvas;
        _canvas = NULL;
    }
}

int sgeApp::exec()
{
    assert(_hWnd == NULL);
    _hWnd = onCreateWND();
    assert(_hWnd);
    _hDC = GetDC(_hWnd);
    _hMem = ::CreateCompatibleDC(_hDC);
    UpdateWindow(_hWnd);
    ShowWindow(_hWnd, SW_SHOW);

    MSG     msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            onRender(_canvas);
            _canvas->writeToBitmap(_buffer, _canvas->width(), _canvas->height());
            BitBlt(_hDC, 0, 0, _canvas->width(), _canvas->height(), _hMem, 0, 0, SRCCOPY);
        }
    }
    return 0;
}

void sgeApp::onResize(int width, int height)
{
    RECT    rt = { 0 };
    GetClientRect(_hWnd, &rt);
    int cw = rt.right - rt.left;
    int ch = rt.bottom - rt.top;

    if (_surface)
    {
        DeleteObject(_surface);
        _surface = NULL;
    }

    BITMAPINFO	bmpInfor;
    bmpInfor.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfor.bmiHeader.biWidth = cw;
    bmpInfor.bmiHeader.biHeight = ch;
    bmpInfor.bmiHeader.biPlanes = 1;
    bmpInfor.bmiHeader.biBitCount = 32;
    bmpInfor.bmiHeader.biCompression = BI_RGB;
    bmpInfor.bmiHeader.biSizeImage = 0;
    bmpInfor.bmiHeader.biXPelsPerMeter = 0;
    bmpInfor.bmiHeader.biYPelsPerMeter = 0;
    bmpInfor.bmiHeader.biClrUsed = 0;
    bmpInfor.bmiHeader.biClrImportant = 0;
    _surface = CreateDIBSection(_hDC, &bmpInfor, DIB_RGB_COLORS, (void**)&_buffer, 0, 0);
    SelectObject(_hMem, _surface);

    if (_canvas) _canvas->resize(cw, ch);
    else _canvas = new Canvas(cw, ch);
}

HWND sgeApp::onCreateWND()
{
    HWND hWnd = CreateWindowEx(
        0
        , WNDCLASSNAME
        , WNDCLASSNAME
        , WS_OVERLAPPEDWINDOW
        , CW_USEDEFAULT
        , CW_USEDEFAULT
        , _width
        , _height
        , NULL
        , 0
        , 0
        , 0);
    return hWnd;
}

LRESULT sgeApp::wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
{
    switch (msgId)
    {
    case WM_SIZE:
        _width = LOWORD(lParam);
        _height = HIWORD(lParam);
        onResize(_width, _height);
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msgId, wParam, lParam);
}