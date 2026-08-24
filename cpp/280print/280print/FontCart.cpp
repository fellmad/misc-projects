#include "stdafx.h"
#include "FontCart.h"

//registry: HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Print\Printers\
//    DataCard 280 (Graphics)\PrinterDriverData


FontCart::FontCart(CString printerName) : _printerName(printerName)
{
    FontCart::CreateFont_FontCartMap();
}

CString FontCart::EnableFontCartForFont(const CString fontName)
{
    CString originalFontCart;


    //dlftodo

    return originalFontCart;
}

void FontCart::CreateFont_FontCartMap()
{
    _font_FontCarts[TEXT("6mm Gothic (7 cpi - Emboss)")] = TEXT("6mm Gothic");
    _font_FontCarts[TEXT("ABA (75 bpi - Mag Stripe)")] = TEXT("Mag Stripe");
    _font_FontCarts[TEXT("Hospital 7B (7 cpi - Emboss)")] = TEXT("Hospital 7B");
    _font_FontCarts[TEXT("Hospital Elite (9 cpi - Emboss)")] = TEXT("Hospital Elite");
    _font_FontCarts[TEXT("IATA (210 bpi - Mag Stripe)")] = TEXT("Mag Stripe");
    _font_FontCarts[TEXT("Large Gothic (7 cpi - Emboss)")] = TEXT("Large Gothic");
    _font_FontCarts[TEXT("MasterCard (14 cpi - Indent)")] = TEXT("MasterCard Indent");
    _font_FontCarts[TEXT("OCR A1 (10 cpi - Indent)")] = TEXT("OCRA1 Indent");
    _font_FontCarts[TEXT("OCR B1 (10 cpi - Indent)")] = TEXT("OCRB1 Indent");
    _font_FontCarts[TEXT("OCR B4 (7 cpi - Electron Indent)")] = TEXT("Electron Indent");
    _font_FontCarts[TEXT("OCR B4 (7 cpi - Emboss)")] = TEXT("OCRB4 Emboss");
    _font_FontCarts[TEXT("OCR B4 (7 cpi - Indent)")] = TEXT("OCRB4 Indent");
    _font_FontCarts[TEXT("Std. Gothic (10 cpi - Emboss)")] = TEXT("Farrington 7B");
    _font_FontCarts[TEXT("Std. Gothic (Cyrillic)")] = TEXT("Standard Gothic (Cyrillic)");
    _font_FontCarts[TEXT("Std.Gothic(10 cpi - Emboss)")] = TEXT("Standard Gothic");
    _font_FontCarts[TEXT("TTS (210 bpi - Mag Stripe)")] = TEXT("Mag Stripe");
}

std::vector <std::wstring> FontCart::Parse_REG_MULTI_SZ(std::vector<byte> data)
{
    std::vector <std::wstring> strings;
    PWCHAR pwchar = (PWCHAR) &data[0];
    while (L'' != *pwchar) {
        std::wstring fontCartridgeName = pwchar;
        strings.push_back(fontCartridgeName);
        pwchar = pwchar + fontCartridgeName.length();
        pwchar++;
    }
    return strings;
}
