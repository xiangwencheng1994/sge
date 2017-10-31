//////////////////////////////////////////////////////////////////////////
// ICanvas.h
//////////////////////////////////////////////////////////////////////////

#ifndef SGE_CANVAS_H
#define SGE_CANVAS_H

#include "sgeMath.h"

namespace sge
{
    /**
     *  »­²¼½Ó¿Ú
     */
    class ICanvas
    {
    public:
        virtual int     width()     = 0;
        virtual int     height()    = 0;
        virtual void    resize(int w, int h)    = 0;

        // draw api
        virtual void    clear()     = 0;
        virtual void    drawPoint(float x, float y, Color4f color) = 0;
        
        //...

    };
}

#endif //!SGE_CANVAS_H