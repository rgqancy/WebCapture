/*
 *  diblib.h
 *
 *  Copyright (c) 1991 Microsoft Corporation. All rights reserved
 *  Modified  (m) 1996 Alessandro Iacopetti
 *
 *  Header file for Device-Independent Bitmap (DIB) API.  Provides
 *  function prototypes and constants for the following functions:
 *
 *  BitmapToDIB()        - Creates a DIB from a bitmap
 *  ChangeBitmapFormat() - Changes a bitmap to a specified DIB format
 *  ChangeDIBFormat()    - Changes a DIB's BPP and/or compression format
 *  CopyScreenToBitmap() - Copies entire screen to a standard Bitmap
 *  CopyScreenToDIB()    - Copies entire screen to a DIB
 *  CopyWindowToBitmap() - Copies a window to a standard Bitmap
 *  CopyWindowToDIB()    - Copies a window to a DIB
 *  CreateDIBPalette()   - Creates a palette from a DIB
 *  CreateDIB()          - Creates a new DIB
 *  DestroyDIB()         - Deletes DIB when finished using it
 *  DIBHeight()          - Gets the DIB height
 *  DIBNumColors()       - Calculates number of colors in the DIB's color table
 *  DIBToBitmap()        - Creates a bitmap from a DIB
 *  DIBWidth()           - Gets the DIB width
 *  FindDIBBits()        - Sets pointer to the DIB bits
 *  GetSystemPalette()   - Gets the current palette
 *  LoadDIB()            - Loads a DIB from a file
 *  PaintBitmap()        - Displays standard bitmap in the specified DC
 *  PaintDIB()           - Displays DIB in the specified DC
 *  PalEntriesOnDevice() - Gets the number of palette entries
 *  PaletteSize()        - Calculates the buffer size required by a palette
 *  SaveDIB()            - Saves the specified dib in a file
 *  DIBPixelAddress()
 *
 * See the file DIBAPI.TXT for more information about these functions.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WINDLL
#define DIBLIBDECL		__declspec(dllexport)
#else
#define DIBLIBDECL		__declspec(dllimport)
#endif

/* Handle to a DIB */
#define HDIB HANDLE

/* Print Area selection */
#define PW_WINDOW        1
#define PW_CLIENT        2

/* DIB Macros*/

// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits"
// parameter is the bit count for the scanline (biWidth * biBitCount),
// and this macro returns the number of DWORD-aligned bytes needed
// to hold those bits.

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

/* Error constants */
enum {
      ERR_MIN = 0,                     // All error #s >= this value
      ERR_NOT_DIB = 0,                 // Tried to load a file, NOT a DIB!
      ERR_MEMORY,                      // Not enough memory!
      ERR_READ,                        // Error reading file!
      ERR_LOCK,                        // Error on a GlobalLock()!
      ERR_OPEN,                        // Error opening a file!
      ERR_CREATEPAL,                   // Error creating palette.
      ERR_GETDC,                       // Couldn't get a DC.
      ERR_CREATEDDB,                   // Error create a DDB.
      ERR_STRETCHBLT,                  // StretchBlt() returned failure.
      ERR_STRETCHDIBITS,               // StretchDIBits() returned failure.
      ERR_SETDIBITSTODEVICE,           // SetDIBitsToDevice() failed.
      ERR_STARTDOC,                    // Error calling StartDoc().
      ERR_NOGDIMODULE,                 // Couldn't find GDI module in memory.
      ERR_SETABORTPROC,                // Error calling SetAbortProc().
      ERR_STARTPAGE,                   // Error calling StartPage().
      ERR_NEWFRAME,                    // Error calling NEWFRAME escape.
      ERR_ENDPAGE,                     // Error calling EndPage().
      ERR_ENDDOC,                      // Error calling EndDoc().
      ERR_SETDIBITS,                   // Error calling SetDIBits().
      ERR_FILENOTFOUND,                // Error opening file in GetDib()
      ERR_INVALIDHANDLE,               // Invalid Handle
      ERR_DIBFUNCTION,                 // Error on call to DIB function
      ERR_MAX                          // All error #s < this value
     };



/* Function prototypes */

HDIB      WINAPI BitmapToDIB (HBITMAP hBitmap, HPALETTE hPal);
HDIB      WINAPI ChangeBitmapFormat (HBITMAP  hBitmap,
                                   WORD     wBitCount,
                                   DWORD    dwCompression,
                                   HPALETTE hPal);
HDIB      WINAPI ChangeDIBFormat (HDIB hDIB, WORD wBitCount,
                                DWORD dwCompression);
HBITMAP   WINAPI CopyScreenToBitmap (LPRECT);
HDIB      WINAPI CopyScreenToDIB (LPRECT);
HBITMAP   WINAPI CopyWindowToBitmap (HWND, WORD);
HDIB      WINAPI CopyWindowToDIB (HWND, WORD);
HPALETTE  WINAPI CreateDIBPalette (HDIB hDIB);
HDIB      WINAPI CreateDIB(DWORD, DWORD, WORD);
WORD      WINAPI DestroyDIB (HDIB);
DWORD     WINAPI DIBHeight (LPSTR lpDIB);
WORD      WINAPI DIBNumColors (LPSTR lpDIB);
HBITMAP   WINAPI DIBToBitmap (HDIB hDIB, HPALETTE hPal);
DWORD     WINAPI DIBWidth (LPSTR lpDIB);
LPSTR     WINAPI FindDIBBits (LPSTR lpDIB);
HPALETTE  WINAPI GetSystemPalette (void);
HDIB      WINAPI LoadDIB (LPSTR);
BOOL      WINAPI PaintBitmap (HDC, LPRECT, HBITMAP, LPRECT, HPALETTE);
BOOL      WINAPI PaintDIB (HDC, LPRECT, HDIB, LPRECT, HPALETTE);
int       WINAPI PalEntriesOnDevice (HDC hDC);
WORD      WINAPI PaletteSize (LPSTR lpDIB);
WORD      WINAPI SaveDIB (HDIB, LPSTR);
BYTE*     WINAPI DIBPixelAddress(LPSTR pDIB, UINT x, UINT y);

#ifdef __cplusplus
};
#endif
