/**************************************************************************\
*
* Copyright (c) 1998-2000, Microsoft Corp.  All Rights Reserved.
* Download by http://www.codefans.net
* Module Name:
*
*   GdiplusBase.h
* * Download by http://www.codefans.net
* Abstract:
*
*   Represents the base class for GDIPlus memory allocation. 
*
\**************************************************************************/

#ifndef _GDIPLUSBASE_H
#define _GDIPLUSBASE_H

class GdiplusBase
{
public:
    void (operator delete)(void* in_pVoid)
    {
       DllExports::GdipFree(in_pVoid);
    }
    void* (operator new)(size_t in_size)
    {
       return DllExports::GdipAlloc(in_size);
    }
    void (operator delete[])(void* in_pVoid)
    {
       DllExports::GdipFree(in_pVoid);
    }
    void* (operator new[])(size_t in_size)
    {
       return DllExports::GdipAlloc(in_size);
    }
};

#endif 

