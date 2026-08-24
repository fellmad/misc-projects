#pragma once

#include <map>
#include <vector>

class FontCart {

public:

    FontCart(CString printerName);
    CString EnableFontCartForFont(const CString fontName);
    static std::vector <std::wstring> Parse_REG_MULTI_SZ(std::vector<byte> data);

private:

    FontCart(); // disable private constructor
    typedef std::map <CString, CString> Font_FontCartMap;
    void CreateFont_FontCartMap();

private:

    Font_FontCartMap _font_FontCarts;
    CString _printerName;
};
