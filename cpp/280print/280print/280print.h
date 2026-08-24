#pragma once

#include <vector>

int DrawMagstripeData(
    CDC&            printerDC,
    const CString   faceName,
    const CString   data);

int Draw3TracksMagStripe(CDC& printerDC);
int DrawPrintedText(CDC& printerDC, const CString printText);
int DrawEmbossText(CDC& printerDC, const CString faceName, const CString text);
void DisplayFontCarts(const HANDLE printerHandle);
