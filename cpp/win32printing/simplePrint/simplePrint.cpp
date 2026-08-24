#include <SDKDDKVer.h>
#include <atlstr.h>

int _tmain(int /*argc*/, _TCHAR* /*argv[]*/)
{
    const CString printername = TEXT("xps card printer");

    HDC hdc = ::CreateDC(NULL, printername, NULL, NULL);
    if (!hdc) throw hdc;

    DOCINFO docinfo{};
    docinfo.cbSize = sizeof docinfo;
    docinfo.lpszDocName = TEXT("xps printer simple print");

    int rc = ::StartDoc(hdc, &docinfo);
    if (rc <= 0) throw rc;

    rc = ::StartPage(hdc);
    if (rc <= 0) throw rc;

    rc = ::EndPage(hdc);
    if (rc <= 0) throw rc;

    CString s = TEXT("some text");
    rc = ::TextOut(hdc, 20, 20, s, s.GetLength());
    if (!rc) {
        throw rc;
    }

    rc = ::EndDoc(hdc);
    if (rc <= 0) throw rc;

    ::DeleteDC(hdc);

    return 0;
}