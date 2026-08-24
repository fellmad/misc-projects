// dlftest
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "StdAfx.h"
#include "../../precomp.h"
#include <msxml6.h>
#include "../../../common/filtertypes.h"
#include "../FlipBackPrintTicketHandler.h"
#include "../FlipFrontPrintTicketHandler.h"
#include "TestFlipPrintTicketHandlers.h"

#pragma comment( lib, "msxml6.lib")

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

/*
  <psf:Feature name="ns0000:PageFlipFront">
    <psf:Option name="ns0000:None" />
  </psf:Feature>

  <psf:Feature name="ns0000:PageFlipBack">
    <psf:Option name="ns0000:None" />
  </psf:Feature>

    <psf:Option name="ns0000:None" constrained="psk:None">
    <psf:Option name="ns0000:Flipped" constrained="psk:None">

    enum EFlipCardSideOptions {
        None = 0, EFlipCardSideOptionsMin = 0,
        Flipped,
        EFlipCardSideOptionsMax
    };
*/

const CComBSTR emptyPrintTicket =
R"(<?xml version="1.0" encoding="UTF-8"?>
<psf:PrintTicket
xmlns:psf="http://schemas.microsoft.com/windows/2003/08/printing/printschemaframework"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xmlns:xsd="http://www.w3.org/2001/XMLSchema"
version="1"
xmlns:psk="http://schemas.microsoft.com/windows/2003/08/printing/printschemakeywords"
xmlns:ns0000="http://schemas.datacard.com/2009/09/printing/XPS_Card_Printer">
</psf:PrintTicket>
)";

const CComBSTR both_flipped_printTicket =
R"(<?xml version="1.0" encoding="UTF-8"?>
<psf:PrintTicket
xmlns:psf="http://schemas.microsoft.com/windows/2003/08/printing/printschemaframework"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xmlns:xsd="http://www.w3.org/2001/XMLSchema"
version="1"
xmlns:psk="http://schemas.microsoft.com/windows/2003/08/printing/printschemakeywords"
xmlns:ns0000="http://schemas.datacard.com/2009/09/printing/XPS_Card_Printer">
  <psf:Feature name="ns0000:PageFlipFront">
    <psf:Option name="ns0000:Flipped" />
  </psf:Feature>
  <psf:Feature name="ns0000:PageFlipBack">
    <psf:Option name="ns0000:Flipped" />
  </psf:Feature>
</psf:PrintTicket>
)";

const CComBSTR badFlipData_printTicket =
R"(<?xml version="1.0" encoding="UTF-8"?>
<psf:PrintTicket
xmlns:psf="http://schemas.microsoft.com/windows/2003/08/printing/printschemaframework"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xmlns:xsd="http://www.w3.org/2001/XMLSchema"
version="1"
xmlns:psk="http://schemas.microsoft.com/windows/2003/08/printing/printschemakeywords"
xmlns:ns0000="http://schemas.datacard.com/2009/09/printing/XPS_Card_Printer">
  <psf:Feature name="ns0000:PageFlipFront">
    <psf:Option name="front: really bad data." />
  </psf:Feature>
  <psf:Feature name="ns0000:PageFlipBack">
    <psf:Option name="front: even worse data." />
  </psf:Feature>
</psf:PrintTicket>
)";

bool TestFlipPrintTicketHandlers::Setup()
{
    // = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

    _crtBreakAlloc = 382;

    const auto flag = _CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF;
    _CrtSetDbgFlag(flag);

    _CrtMemCheckpoint(&_start_mem_state);
    return true;
}

bool TestFlipPrintTicketHandlers::Cleanup()
{
    _CrtMemState current_mem_state {};
    _CrtMemCheckpoint(&current_mem_state);

    _CrtMemState diff_mem_state {};
    _CrtMemDifference(&diff_mem_state, &_start_mem_state, &current_mem_state);

    _CrtMemDumpStatistics(&diff_mem_state);

    _CrtDumpMemoryLeaks();

    return true;
}

void TestFlipPrintTicketHandlers::TestGetFromEmptyTicketReturnsNotFound()
{
    SafeCoInit coInit;
    CComPtr <IXMLDOMDocument2> printTicketDomDoc;
    HRESULT hr = printTicketDomDoc.CoCreateInstance(__uuidof(DOMDocument60));
    VERIFY_IS_TRUE(SUCCEEDED(hr));

    VARIANT_BOOL bSuccess(VARIANT_FALSE);
    hr = printTicketDomDoc->loadXML(emptyPrintTicket, &bSuccess);
    VERIFY_IS_TRUE(SUCCEEDED(hr));
    VERIFY_ARE_EQUAL(bSuccess, VARIANT_TRUE);

    FlipFrontPrintTicketHandler frontHandler(printTicketDomDoc);
    XDPrintSchema::FlipCardSide::FlipCardSideData data {};
    VERIFY_ARE_EQUAL(XDPrintSchema::FlipCardSide::None, data._flipSetting);

    hr = frontHandler.GetData(&data);
    VERIFY_ARE_EQUAL(E_ELEMENT_NOT_FOUND, hr);

    FlipBackPrintTicketHandler backHandler(printTicketDomDoc);
    hr = backHandler.GetData(&data);
    VERIFY_ARE_EQUAL(E_ELEMENT_NOT_FOUND, hr);
}

void TestFlipPrintTicketHandlers::TestGetDataWithNullPointer()
{
    SafeCoInit coInit;
    CComPtr <IXMLDOMDocument2> printTicketDomDoc;
    HRESULT hr = printTicketDomDoc.CoCreateInstance(__uuidof(DOMDocument60));
    VERIFY_IS_TRUE(SUCCEEDED(hr));

    VARIANT_BOOL bSuccess(VARIANT_FALSE);
    hr = printTicketDomDoc->loadXML(emptyPrintTicket, &bSuccess);
    VERIFY_IS_TRUE(SUCCEEDED(hr));
    VERIFY_ARE_EQUAL(bSuccess, VARIANT_TRUE);

    FlipFrontPrintTicketHandler frontHandler(printTicketDomDoc);
    XDPrintSchema::FlipCardSide::FlipCardSideData* data {nullptr};
    hr = frontHandler.GetData(data);
    VERIFY_ARE_EQUAL(E_POINTER, hr);

    FlipBackPrintTicketHandler backHandler(printTicketDomDoc);
    hr = frontHandler.GetData(data);
    VERIFY_ARE_EQUAL(E_POINTER, hr);
}

void TestFlipPrintTicketHandlers::TestSetDataWithNullPointer()
{
    SafeCoInit coInit;
    CComPtr <IXMLDOMDocument2> printTicketDomDoc;
    HRESULT hr = printTicketDomDoc.CoCreateInstance(__uuidof(DOMDocument60));
    VERIFY_IS_TRUE(SUCCEEDED(hr));

    VARIANT_BOOL bSuccess(VARIANT_FALSE);
    hr = printTicketDomDoc->loadXML(emptyPrintTicket, &bSuccess);
    VERIFY_IS_TRUE(SUCCEEDED(hr));
    VERIFY_ARE_EQUAL(bSuccess, VARIANT_TRUE);

    FlipFrontPrintTicketHandler frontHandler(printTicketDomDoc);
    XDPrintSchema::FlipCardSide::FlipCardSideData* data {nullptr};
    hr = frontHandler.SetData(data);
    VERIFY_ARE_EQUAL(E_POINTER, hr);

    FlipBackPrintTicketHandler backHandler(printTicketDomDoc);
    hr = frontHandler.SetData(data);
    VERIFY_ARE_EQUAL(E_POINTER, hr);
}

void TestFlipPrintTicketHandlers::TestReturnedFlipped()
{
    SafeCoInit coInit;
    CComPtr <IXMLDOMDocument2> printTicketDomDoc;
    HRESULT hr = printTicketDomDoc.CoCreateInstance(__uuidof(DOMDocument60));
    VERIFY_IS_TRUE(SUCCEEDED(hr));

    VARIANT_BOOL bSuccess(VARIANT_FALSE);
    hr = printTicketDomDoc->loadXML(both_flipped_printTicket, &bSuccess);
    VERIFY_IS_TRUE(SUCCEEDED(hr));
    VERIFY_ARE_EQUAL(bSuccess, VARIANT_TRUE);

    FlipFrontPrintTicketHandler frontHandler(printTicketDomDoc);
    XDPrintSchema::FlipCardSide::FlipCardSideData frontData {};
    hr = frontHandler.GetData(&frontData);
    VERIFY_IS_TRUE(SUCCEEDED(hr));
    VERIFY_ARE_EQUAL(XDPrintSchema::FlipCardSide::Flipped, frontData._flipSetting);

    FlipBackPrintTicketHandler backHandler(printTicketDomDoc);
    XDPrintSchema::FlipCardSide::FlipCardSideData backData {};
    hr = backHandler.GetData(&backData);
    VERIFY_IS_TRUE(SUCCEEDED(hr));
    VERIFY_ARE_EQUAL(XDPrintSchema::FlipCardSide::Flipped, backData._flipSetting);
}

void TestFlipPrintTicketHandlers::TestGet_BadData()
{
    SafeCoInit coInit;
    CComPtr <IXMLDOMDocument2> printTicketDomDoc;
    HRESULT hr = printTicketDomDoc.CoCreateInstance(__uuidof(DOMDocument60));
    VERIFY_IS_TRUE(SUCCEEDED(hr));

    VARIANT_BOOL bSuccess(VARIANT_FALSE);
    hr = printTicketDomDoc->loadXML(badFlipData_printTicket, &bSuccess);
    VERIFY_IS_TRUE(SUCCEEDED(hr));
    VERIFY_ARE_EQUAL(bSuccess, VARIANT_TRUE);

    FlipFrontPrintTicketHandler frontHandler(printTicketDomDoc);
    XDPrintSchema::FlipCardSide::FlipCardSideData frontData {};
    hr = frontHandler.GetData(&frontData);
    VERIFY_ARE_EQUAL(E_INVALIDARG, hr);

    FlipBackPrintTicketHandler backHandler(printTicketDomDoc);
    XDPrintSchema::FlipCardSide::FlipCardSideData backData {};
    hr = backHandler.GetData(&backData);
    VERIFY_ARE_EQUAL(E_INVALIDARG, hr);
}

void TestFlipPrintTicketHandlers::TestSet_BadData()
{
    SafeCoInit coInit;
    CComPtr <IXMLDOMDocument2> printTicketDomDoc;
    HRESULT hr = printTicketDomDoc.CoCreateInstance(__uuidof(DOMDocument60));
    VERIFY_IS_TRUE(SUCCEEDED(hr));

    VARIANT_BOOL bSuccess(VARIANT_FALSE);
    hr = printTicketDomDoc->loadXML(emptyPrintTicket, &bSuccess);
    VERIFY_IS_TRUE(SUCCEEDED(hr));
    VERIFY_ARE_EQUAL(bSuccess, VARIANT_TRUE);

    FlipFrontPrintTicketHandler frontHandler(printTicketDomDoc);
    XDPrintSchema::FlipCardSide::FlipCardSideData frontData {};
    frontData._flipSetting = 
        static_cast<XDPrintSchema::FlipCardSide::EFlipCardSideOptions> (12345);
    hr = frontHandler.SetData(&frontData);
    VERIFY_ARE_EQUAL(E_INVALIDARG, hr);


    _pbyte = new byte[1234];



    FlipBackPrintTicketHandler backHandler(printTicketDomDoc);
    XDPrintSchema::FlipCardSide::FlipCardSideData backData {};
    backData._flipSetting =
        static_cast<XDPrintSchema::FlipCardSide::EFlipCardSideOptions> (54321);
    hr = backHandler.SetData(&backData);
    VERIFY_ARE_EQUAL(E_INVALIDARG, hr);
}