// http://support.microsoft.com/kb/201978 

#include "stdafx.h"
#include "XGetopt.h"
#include <iostream>

using namespace std;

void usage() {
    cout << "options:" << endl;
    cout << "  -n <printername>" << endl;
}

CString StringFromFontType(const DWORD fontType)
{
    ///* EnumFonts Masks */
    //#define RASTER_FONTTYPE     0x0001
    //#define DEVICE_FONTTYPE     0x0002
    //#define TRUETYPE_FONTTYPE   0x0004

    if (0 == fontType) return TEXT("undefined");

    CString s;
    if (fontType & RASTER_FONTTYPE) s += " raster";
    if (fontType & DEVICE_FONTTYPE) s += " device";
    if (fontType & TRUETYPE_FONTTYPE) s += " truetype";
    return s.Trim();
}

struct ENUMEDFONT {
    DWORD          FontType;
    ENUMLOGFONTEX* elfx;
};

// Data structure to pass data through the font enumeration callbacks.
struct PRINTENUMFONTDATA {
    HDC             hPrinterDC;
    HDC             hEnumDC;
    int             curx;
    int             cury;
    ENUMLOGFONTEX   elf;
};

/*
Returns true if the two ENUMLOGFONTEX buffers compare.
Return false if the two buffers differ in someway as described by the
criteria below.
*/
BOOL CompareLogFontEx(
    const ENUMLOGFONTEX* Destination,    // copy destination
    const ENUMLOGFONTEX* Source)         // memory block
{
    // Compare the string descriptions:
    if (lstrcmpi((LPCTSTR)Destination->elfFullName, (LPCTSTR)Source->elfFullName) != 0)
        return false;
    if (lstrcmpi((LPCTSTR)Destination->elfScript, (LPCTSTR)Source->elfScript) != 0)
        return false;
    if (lstrcmpi((LPCTSTR)Destination->elfStyle, (LPCTSTR)Source->elfStyle) != 0)
        return false;

    // Height and Width are not compared because they will change
    // based upon the device on which the font is enumerated.
    //  LONG lfHeight; 
    //  LONG lfWidth; 

    // Compare the LOGFONT properties:
    //  LONG lfEscapement; 
    if (Destination->elfLogFont.lfEscapement != Source->elfLogFont.lfEscapement) return false;
    //  LONG lfOrientation; 
    if (Destination->elfLogFont.lfOrientation != Source->elfLogFont.lfOrientation) return false;
    //  LONG lfWeight; 
    if (Destination->elfLogFont.lfWeight != Source->elfLogFont.lfWeight) return false;
    //  BYTE lfItalic; 
    if (Destination->elfLogFont.lfItalic != Source->elfLogFont.lfItalic) return false;
    //  BYTE lfUnderline; 
    if (Destination->elfLogFont.lfUnderline != Source->elfLogFont.lfUnderline) return false;
    //  BYTE lfStrikeOut; 
    if (Destination->elfLogFont.lfStrikeOut != Source->elfLogFont.lfStrikeOut) return false;
    //  BYTE lfCharSet; 
    if (Destination->elfLogFont.lfCharSet != Source->elfLogFont.lfCharSet) return false;
    //  BYTE lfOutPrecision; 
    if (Destination->elfLogFont.lfOutPrecision != Source->elfLogFont.lfOutPrecision) return false;
    //  BYTE lfClipPrecision; 
    if (Destination->elfLogFont.lfClipPrecision != Source->elfLogFont.lfClipPrecision) return false;
    //  BYTE lfQuality; 
    if (Destination->elfLogFont.lfQuality != Source->elfLogFont.lfQuality) return false;
    //  BYTE lfPitchAndFamily; 
    if (Destination->elfLogFont.lfPitchAndFamily != Source->elfLogFont.lfPitchAndFamily) return false;
    //  TCHAR lfFaceName[LF_FACESIZE]; 
    if (lstrcmpi((LPCTSTR)Destination->elfLogFont.lfFaceName, (LPCTSTR)Source->elfLogFont.lfFaceName) != 0) return false;

    // Conclusion: the two LOGFONT enumeration buffers are comparable.
    return true;
}

int CALLBACK FindSystemFontEnum(
    ENUMLOGFONTEX* lpelfe,     // logical-font data
    NEWTEXTMETRICEX* lpntme,     // physical-font data
    DWORD               FontType,   // type of font
    LPARAM              lParam)     // application-defined data
{
    ENUMEDFONT* pdf = (ENUMEDFONT*)lParam;
    ENUMLOGFONTEX* lpelfeSrc = pdf->elfx;

    lpelfe->elfLogFont.lfHeight = lpelfeSrc->elfLogFont.lfHeight;
    lpelfe->elfLogFont.lfWidth = lpelfeSrc->elfLogFont.lfWidth;

    if (CompareLogFontEx(lpelfeSrc, lpelfe) && FontType == pdf->FontType)
        return 0;       // System font found. Stop enumeration.
    return 1;
}

/*
Utility function that takes a font that is enumerated from a printer device
that is in the pdf parameter and that looks for it on a Screen Device
Context to conclude that the font passed in that came from the
printer is really supplied by the system.
*/
BOOL IsSystemFont(ENUMEDFONT* pdf)
{
    HDC hScreenDC = GetDC(NULL);    // Get the screen device context.

    // If the enumeration stops by returning zero (0),
    // the font was found on the screen device context so it is a 
    // system-supplied font.
    BOOL fFound = !::EnumFontFamiliesEx(
        hScreenDC,
        &pdf->elfx->elfLogFont,
        (FONTENUMPROC)FindSystemFontEnum,
        (LPARAM)pdf,
        0);

    ReleaseDC(NULL, hScreenDC);

    return fFound;
}

int CALLBACK PrinterDeviceFontEnum(
    ENUMLOGFONTEX* lpelfe,     // logical-font data
    NEWTEXTMETRICEX* lpntme,     // physical-font data
    DWORD               FontType,   // type of font
    LPARAM              lParam)     // application-defined data
{
    // Crack the data out of the enumeration parameter.
    PRINTENUMFONTDATA* ppeft = (PRINTENUMFONTDATA*)lParam;

    // Printing information
    TEXTMETRIC tm;
    HFONT hfont, holdfont;
    int pagecx, pagecy;

    // Data to determine where this font came from
    ENUMEDFONT df = { FontType, lpelfe };  // To look for a system version

    // What is the printable area of the page?
    pagecx = GetDeviceCaps(ppeft->hPrinterDC, HORZRES);
    pagecy = GetDeviceCaps(ppeft->hPrinterDC, VERTRES);

    // Is it a device font?
    // If it is, make sure that it is also not a TrueType font because
    // that is most likely a downloaded font.
    // Also, look for any system-provided fonts that are also 
    // masquerading as printer device fonts. This implies that they will be 
    // downloaded to the printer as is the case with Adobe Type 1 fonts.
    // If they are downloaded, you do not want to include them in this demonstration.
    if (
        (FontType & DEVICE_FONTTYPE) &&
        !(FontType & TRUETYPE_FONTTYPE) &&
        !IsSystemFont(&df)) {
        TCHAR   Buffer[MAX_PATH] = { 0 };     // description of font
        LPTSTR  szFontType(NULL);           // description of type
        LPTSTR  pStyle = TEXT("Regular");   // Fonts Style defaults to Regular 

        // At this point in this code, the lpelfe parameter has been examined
        // and found to describe a printer device font.
        // Do something interesting with it as follows:

        // Build a sample string that describes the font.
        if (lpelfe->elfLogFont.lfItalic) {
            pStyle = TEXT("Italic");
            if (lpelfe->elfLogFont.lfWeight > FW_NORMAL)
                pStyle = TEXT("Bold Italic");
        }
        else {
            if (lpelfe->elfLogFont.lfWeight > FW_NORMAL)
                pStyle = TEXT("Bold");
        }

        // Determine if the font is scalable or a bitmap font.
        if (FontType & RASTER_FONTTYPE) {
            szFontType = TEXT("Bitmap Font");
        }
        else {
            // This is an instance of a scalable font, 
            // use 12 pt because it is easy to read.
            szFontType = TEXT("Scalable Font");
            lpelfe->elfLogFont.lfHeight = MulDiv(12, GetDeviceCaps(ppeft->hPrinterDC, LOGPIXELSY), 72);
            lpelfe->elfLogFont.lfWidth = 0;
        }

        // Skip all fonts after this font that are the same scale as the last one.
        // However, let different sizes of 'bitmap' fonts through.
        // This is a cheat that relies on enumeration order.
        // Really, you should keep a 'used' list and compare against the list.
        if (FontType & RASTER_FONTTYPE || !CompareLogFontEx(&ppeft->elf, lpelfe)) {

            hfont = CreateFontIndirect(&lpelfe->elfLogFont);
            holdfont = (HFONT)SelectObject(ppeft->hPrinterDC, hfont);
            GetTextMetrics(ppeft->hPrinterDC, &tm);

            // If beyond bottom of page, get a new page.
            if (pagecy < ppeft->cury + tm.tmExternalLeading + tm.tmHeight) {
                EndPage(ppeft->hPrinterDC);
                StartPage(ppeft->hPrinterDC);
                ppeft->cury = 0;
            }

            // Draw our sample text.
            wsprintf(Buffer, L"%s %s [%s]  FontType: %s", lpelfe->elfFullName, pStyle, lpelfe->elfScript, szFontType);
            ppeft->cury += tm.tmExternalLeading;
            TextOut(ppeft->hPrinterDC, ppeft->curx, ppeft->cury, Buffer, lstrlen(Buffer));
            ppeft->cury += tm.tmHeight;

            // Clean up.
            SelectObject(ppeft->hPrinterDC, holdfont);
            DeleteObject(hfont);

            // Make a note of the font that you used so that the next time
            // this callback is called, you can skip different scales of 
            // the same font.
            CopyMemory(&ppeft->elf, lpelfe, sizeof(ENUMLOGFONTEX));
        }
    }

    // Otherwise, continue enumeration without doing anything with this
    // particular font.

    return 1;
}

int CALLBACK EnumFontFamiliesCallback(
    ENUMLOGFONTEX* lpelfe,     // logical-font data
    NEWTEXTMETRICEX* lpntme,     // physical-font data
    DWORD               fontType,   // type of font
    LPARAM              lParam)     // application-defined data
{
    PRINTENUMFONTDATA* ppeft = (PRINTENUMFONTDATA*)lParam;
    ZeroMemory(&ppeft->elf, sizeof(ppeft->elf));

    wcout <<
        "'" << lpelfe->elfFullName << "' " <<
        "'" << lpelfe->elfLogFont.lfFaceName << "' "
        "'" << lpelfe->elfScript << "'" <<
        " " << StringFromFontType(fontType).GetBuffer() <<
        endl;

    if (fontType & DEVICE_FONTTYPE && fontType & DEVICE_FONTTYPE) {
        int rc = ::EnumFontFamiliesEx(
            ppeft->hEnumDC,
            &lpelfe->elfLogFont,
            (FONTENUMPROC)PrinterDeviceFontEnum,
            lParam,
            0);

        return rc;
    }

    // Otherwise, if you are not interested in this particular font, 
    // continue enumeration so that you can find more.
    return 1;
}

void PrintDeviceFontList(const HDC hPrinterDC)
{
    PRINTENUMFONTDATA peft = {
        hPrinterDC, // Device Context on which to print
        hPrinterDC, // Device Context to enumerate 
        0, 0,       // Current print location
        NULL        // Last device font that is used to print
    };

    LOGFONT lf = { 0 };
    lf.lfCharSet = DEFAULT_CHARSET;

    wcout <<
        "'" << "lpelfe->elfFullName" << "' " <<
        "'" << "lpelfe->elfLogFont.lfFaceName" << "' "
        "'" << "lpelfe->elfScript" << "'" <<
        endl;

    // Call the enumeration with your callback function that prints
    // the device fonts that it finds.
    int ret = ::EnumFontFamiliesEx(
        hPrinterDC,
        &lf,
        (FONTENUMPROC)EnumFontFamiliesCallback,
        (LPARAM)&peft,
        0);
}

int _tmain(int argc, _TCHAR* argv[])
{
    CString printerName;

    int c(0);
    while ((c = getopt(argc, argv, _T("n:rpicj"))) != EOF) {
        switch (c) {
        case TEXT('n'): printerName = optarg; break;
        default: usage();
        }
    }

    if (printerName.IsEmpty()) {
        usage();
        printerName = TEXT("DataCard 280 (Graphics)");
        cout << "using default printername: '" << CT2A(printerName) << "'" << endl << endl;
    }

    const HDC hdc = ::CreateDC(NULL, printerName, NULL, NULL);

    if (NULL == hdc) {
        cerr << "CreateDC() error " << ::GetLastError() << endl;
        return -1;
    }

    PrintDeviceFontList(hdc);

    ::DeleteDC(hdc);

    return 0;
}
