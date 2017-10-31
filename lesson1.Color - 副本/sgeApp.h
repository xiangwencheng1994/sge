//////////////////////////////////////////////////////////////////////////
// sgeApp.h
// 用来定义应用程序接口
//////////////////////////////////////////////////////////////////////////

#ifndef SGE_APP_H
#define SGE_APP_H

#include "sgeCanvas.h"

namespace sge
{
    class IApp
    {
    public:
        virtual int     width()     = 0;
        virtual int     height()    = 0;
        virtual int     exec()      = 0;
    protected:
        virtual void    onRender(ICanvas *canvas)  = 0;
    };
}

#ifdef WIN32
#include "sgeWin32App.h"
namespace sge
{
    typedef class Win32App App; 
}
#endif // WIN32

#endif //!SGE_APP_H
