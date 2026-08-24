#include <SDKDDKVer.h>
#include <atlbase.h>
#include <iostream>
#include <string>
#include <vector>

struct PrinterInfo {
    int windowsJobID;
    std::wstring printerName;
    std::vector <std::wstring> itemNames;
};

int wmain(int /*argc*/, WCHAR* /*argv*/[])
{
    // in FIRST filter:
    PrinterInfo* printerInfo1 = new PrinterInfo {
        123,
        L"xps card printer",
        {L"item1", L"item2", L"item3"}
    };

    CComVariant var1;
    var1 = reinterpret_cast <BYTE*> (printerInfo1);

    // stuff var1 into the Print Filter Property Bag. Use windowsJobID (as a
    // string) as the unique key. IPrintPipelinePropertyBag->AddProperty().

    // do NOT delete allocated memory for the PrinterInfo object.
    // we now have an 'apparent' leak in this filter...'apparent'.

    // downstream...in any other filter:
    // IPrintPipelinePropertyBag->GetProperty() using windowsJobID as string
    CComVariant var2 = var1;  // simulating the GetProperty() call...

    PrinterInfo* printerInfo2 = reinterpret_cast <PrinterInfo*> (var2.pbVal);

    const auto windowsJobId = printerInfo2->windowsJobID;
    const auto printerName = printerInfo2->printerName;
    const auto itemNames = printerInfo2->itemNames;

    // in the VERY LAST filter..at the END of ::StartOperation()...delete the
    // previously allocated memory from the FIRST filter...or intermediate
    // filters:
    delete printerInfo2;
    printerInfo2 = nullptr;
}