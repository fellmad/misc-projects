#include "stdafx.h"
#include <winspool.h>
#include "DevMode.h"
#include "XGetopt.h"
#include "FontCart.h"
#include "280print.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

const CString iataFontName = TEXT("IATA (210 bpi - Mag Stripe)");
const CString abaFontName = TEXT("ABA (75 bpi - Mag Stripe)");
const CString ttsFontName = TEXT("TTS (210 bpi - Mag Stripe)");

int DrawMagstripeData(
    CDC&            printerDC,
    const CString   faceName,
    const CString   data)
{
    CFont font;
    LOGFONT logFont = {0};
    _tcsncpy_s(logFont.lfFaceName, LF_FACESIZE, faceName, faceName.GetLength());

    int rc = font.CreateFontIndirect(&logFont);
    if (!rc) {
        _tprintf(_T("font.CreateFontIndirect() fail: %d\n"), ::GetLastError());
        return -1;
    }

    CFont* defaultFont = printerDC.SelectObject(&font);
    if (NULL == defaultFont) {
        _tprintf(_T("SelectObject(iata font) fail: %d\n"), ::GetLastError());
        return -1;
    }

    rc = printerDC.TextOut(50, 30, data);
    if (0 == rc) {
        _tprintf(_T("TextOut() fail: %d\n"), ::GetLastError());
        return -1;
    }

    const CFont* dummyFont = printerDC.SelectObject(defaultFont);
    if (NULL == dummyFont) {
        _tprintf(_T("SelectObject(original font) fail: %d\n"), ::GetLastError());
        return -1;
    }

    return 0;
}

int Draw3TracksMagStripe(CDC& printerDC)
{
    // dlfnote: if we do more that one magstripe track ... we get the dreaded
    // one-cpx-command-per-char problem.

    //int rc = DrawMagstripeData(printerDC, iataFontName, TEXT("ABCD 1234"));
    //if (FAILED(rc)) {
    //    _tprintf(_T("DrawMagstripeData(%s) %d\n"), iataFontName, ::GetLastError());
    //    return -1;
    //}

    //rc = DrawMagstripeData(printerDC, abaFontName, TEXT("56789"));
    //if (FAILED(rc)) {
    //    _tprintf(_T("DrawMagstripeData(%s) %d\n"), abaFontName, ::GetLastError());
    //    return -1;
    //}

    int rc = DrawMagstripeData(printerDC, ttsFontName, TEXT("123451234567890"));
    if (FAILED(rc)) {
        _tprintf(_T("DrawMagstripeData(%s) %d\n"), ttsFontName, ::GetLastError());
        return -1;
    }

    return 0;
}

int DrawPrintedText(CDC& printerDC, const CString printText)
{
    CFont font;
    int rc = font.CreateFont(
        48,                         // nHeight
        0,                          // nWidth
        0,                          // nEscapement
        0,                          // nOrientation
        FW_NORMAL,                  // nWeight
        FALSE,                      // bItalic
        FALSE,                      // bUnderline
        0,                          // cStrikeOut
        ANSI_CHARSET,               // nCharSet
        OUT_DEFAULT_PRECIS,         // nOutPrecision
        CLIP_DEFAULT_PRECIS,        // nClipPrecision
        DEFAULT_QUALITY,            // nQuality
        DEFAULT_PITCH | FF_SWISS,   // nPitchAndFamily
        _T("Arial"));               // lpszFacename

    if (0 == rc) {
        _tprintf(_T("CreateFont() fail: %d\n"), ::GetLastError());
        return -1;
    }

    CFont* defaultFont = printerDC.SelectObject(&font);
    if (NULL == defaultFont) {
        _tprintf(_T("SelectObject(iata font) fail: %d\n"), ::GetLastError());
        return -1;
    }

    rc = printerDC.TextOut(20, 300, printText);
    if (0 == rc) {
        _tprintf(_T("TextOut() fail: %d\n"), ::GetLastError());
        return -1;
    }

    const CFont* dummyFont = printerDC.SelectObject(defaultFont);
    if (NULL == dummyFont) {
        _tprintf(_T("SelectObject(original font) fail: %d\n"), ::GetLastError());
        return -1;
    }

    return rc;
}

int DrawEmbossText(CDC& printerDC, const CString faceName, const CString text)
{
    CFont font;
    int rc = font.CreateFont(
        0,                      // nHeight
        0,                      // nWidth
        0,                      // nEscapement
        0,                      // nOrientation
        FW_DONTCARE,            // nWeight
        FALSE,                  // bItalic
        FALSE,                  // bUnderline
        0,                      // cStrikeOut
        ANSI_CHARSET,           // nCharSet
        OUT_DEFAULT_PRECIS,     // nOutPrecision
        CLIP_DEFAULT_PRECIS,    // nClipPrecision
        DEFAULT_QUALITY,        // nQuality
        DEFAULT_PITCH,          // nPitchAndFamily
        faceName);

    if (0 == rc) {
        _tprintf(_T("CreateFont() fail: %d\n"), ::GetLastError());
        return -1;
    }

    CFont* defaultFont = printerDC.SelectObject(&font);
    if (NULL == defaultFont) {
        _tprintf(_T("SelectObject(font) fail: %d\n"), ::GetLastError());
        return -1;
    }

    rc = printerDC.TextOut(50, 200, text);
    if (0 == rc) {
        _tprintf(_T("TextOut() fail: %d\n"), ::GetLastError());
        return -1;
    }

    const CFont* dummyFont = printerDC.SelectObject(defaultFont);
    if (NULL == dummyFont) {
        _tprintf(_T("SelectObject(font) fail: %d\n"), ::GetLastError());
        return -1;
    }

    return 0;
}

void DisplayFontCarts(const HANDLE printerHandle)
{
    const CString printerDriverDataKeyName(TEXT("PrinterDriverData"));
    const CString fontCartValueName(TEXT("FontCart"));
    const size_t fontCartBufferSize(1024);
    std::vector <byte> fontCartBytes(fontCartBufferSize);
    DWORD dataType(0);
    DWORD bytesNeeded(0);

    int rc = ::GetPrinterDataEx(
        printerHandle,
        printerDriverDataKeyName,
        fontCartValueName,
        &dataType,
        &fontCartBytes[0],
        fontCartBufferSize,
        &bytesNeeded);

    if (ERROR_SUCCESS != rc) {
        _tprintf(_T("GetPrinterDataEx() fail: %d\n"), ::GetLastError());
        return;
    }

    std::vector <std::wstring> strings = FontCart::Parse_REG_MULTI_SZ(fontCartBytes);

    std::cout << "font cartridge names:" << std::endl;
    for (size_t i = 0; i < strings.size(); i++) {
        std::wcout << "  " << strings[i].c_str() << std::endl;
    }
}

int _tmain(int /*argc*/, TCHAR* /*argv[]*/, TCHAR* /*envp[]*/)
{
    const HMODULE hModule = ::GetModuleHandle(NULL);

    if (hModule != NULL) {
        if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0)) {
            _tprintf(_T("Fatal Error: MFC initialization failed\n"));
            return -1;
        }
    }
    else {
        _tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
        return -1;
    }

    const CString printerName = TEXT("DataCard 280 (Graphics)");

    CDevMode devMode(printerName);
    devMode.SetLandScape();

    DisplayFontCarts(devMode.GetHandle());

    CDC printerDC;
    int rc = printerDC.CreateDC(NULL, printerName, NULL, devMode._devModePointer);
    if (0 == rc) {
        _tprintf(_T("CreateDC() fail: %d\n"), ::GetLastError());
        return -1;
    }

    rc = printerDC.StartDoc(TEXT("280 print test"));
    if (rc <= 0) {
        _tprintf(_T("StartDoc() fail: %d\n"), ::GetLastError());
        return -1;
    }

    rc = printerDC.StartPage();
    if (rc <= 0) {
        _tprintf(_T("StartPage() fail: %d\n"), ::GetLastError());
        return -1;
    }

    CString faceName = TEXT("Large Gothic (7 cpi - Emboss)");
    CString embossText = TEXT("0123456789O large gothic");
    CString printText = TEXT("Large Gothic (7 cpi - Emboss)");

    rc = DrawEmbossText(printerDC, faceName, embossText);
    if (FAILED(rc)) {
        _tprintf(_T("DrawEmbossText(%s) fail %d\n"), faceName, ::GetLastError());
        return -1;
    }

    //rc = DrawPrintedText(printerDC, printText);
    //if (FAILED(rc)) {
    //    _tprintf(_T("DrawPrintedText(%s) fail\n"), printText, ::GetLastError());
    //    return -1;
    //}

    //rc = Draw3TracksMagStripe(printerDC);
    //if (FAILED(rc))
    //    return -1;

    rc = printerDC.EndPage();
    if (rc <= 0) {
        _tprintf(_T("EndPage() fail: %d\n"), ::GetLastError());
        return -1;
    }

    rc = printerDC.EndDoc();
    if (rc <= 0) {
        _tprintf(_T("EndDoc() fail: %d\n"), ::GetLastError());
        return -1;
    }

    return 0;
}
