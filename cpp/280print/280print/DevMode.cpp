////////////////////////////////////////////////////////////////////////////////
// Implementation of the CDevMode class...a simple C++ class that wraps the
// goofy Win32 DEVMODE structure.
////////////////////$Nokeywords:$///////////////////////////////////////////////
#include "stdafx.h"
#include <WinSpool.h>
#include <iostream>
#include "DevMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CDone {
};

////////////////////////////////////////////////////////////////////////////////
// CDevMode::~CDevMode()
// Destructor.
////////////////////////////////////////////////////////////////////////////////
CDevMode::~CDevMode()
{
    if (static_cast<HANDLE>(0) != _printerHandle)
        ::ClosePrinter(_printerHandle);

    if (static_cast<LPDEVMODE>(0) != _devModePointer) {
        delete[] _devModePointer;
    }
}

////////////////////////////////////////////////////////////////////////////////
// CDevMode::IsValid()
//
// return TRUE only if we've successfuly gotten a valid pointer to a DEVMODE
// structure and a valid HANDLE to a printer
////////////////////////////////////////////////////////////////////////////////
bool CDevMode::IsValid()
{
    bool bRC =
        (static_cast<HANDLE>(0) != _printerHandle) &&
        (static_cast<LPDEVMODE>(0) != _devModePointer);
    return bRC;
}

////////////////////////////////////////////////////////////////////////////////
// CDevMode::CDevMode()
//
// Our one & only constructor
//
// Allocate memory for a DEVMODE structure; keep a pointer to it.
// Get & keep a valid HANDLE to the printer.
////////////////////////////////////////////////////////////////////////////////
CDevMode::CDevMode(CString printerName) :
_printerHandle(static_cast<HANDLE>(0)),
_devModePointer(static_cast<LPDEVMODE>(0))
{
    try {
        // get a valid printer handle:
        if (!::OpenPrinter(printerName.GetBuffer(), &_printerHandle, NULL)) {
            CString s;
            s.Format(TEXT("OpenPrinter() %ld"), ::GetLastError());
            std::cerr << CT2A(s) << std::endl;
            CDone e; throw e;
        }

        // Get the required buffer size:
        DWORD dwNeeded = ::DocumentProperties(
            0,
            _printerHandle,     /* handle to our printer */
            printerName.GetBuffer(),
            NULL,           /* Asking for size so */
            NULL,           /* these are not used. */
            0);             /* Zero returns buffer size. */
        if (0 > dwNeeded) {
            CString s;
            s.Format(TEXT("DocumentProperties() %ld"), ::GetLastError());
            std::cerr << CT2A(s) << std::endl;
            CDone e; throw e;
        }

        // Allocate a buffer of the correct size:
        _devModePointer = reinterpret_cast<LPDEVMODE> (new BYTE[dwNeeded]);

        // Get the default DevMode for the printer
        DWORD dwRet = ::DocumentProperties(
            0,
            _printerHandle,
            printerName.GetBuffer(),
            _devModePointer,     /* The address of the buffer to fill. */
            NULL,           /* Not using the input buffer. */
            DM_OUT_BUFFER); /* Have the output buffer filled. */
        if (IDOK != dwRet) {
            CString s;
            s.Format(TEXT("DocumentProperties() %ld"), ::GetLastError());
            std::cerr << CT2A(s) << std::endl;
            CDone e; throw e;
        }

        // At this point, we should have a valid pointer to the DEVMODE in
        // m_pDevMode.  We're done.
    }
    catch (CDone) {
        // we've already logged it.
    }
    catch (...) {
        // A REAL exception occured.
        CString s = TEXT("DocumentProperties() when not logged onto the network will cause this");
        std::cerr << CT2A(s) << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////
// CDevMode::SetPortrait()
//
// force the DEVMODE to "portrain" orientation...if it's possible.
////////////////////////////////////////////////////////////////////////////////
bool CDevMode::SetPortrait()
{
    bool bRC(false);

    if (!IsValid())
        return bRC;

    if (_devModePointer->dmFields & DM_ORIENTATION) {
        /* if the printer supports paper orientation, set it*/
        _devModePointer->dmOrientation = DMORIENT_PORTRAIT;

        // Need to refresh the
        Update();
        bRC = true;
    }
    return bRC;
}

///////////////////////////////////////////////////////////////////////////////
// CDevMode::SetLandScape()
//
// force the DEVMODE to "landscape" orientation...if it's possible.
///////////////////////////////////////////////////////////////////////////////
bool CDevMode::SetLandScape()
{
    bool bRC(false);

    if (!IsValid())
        return bRC;

    if (_devModePointer->dmFields & DM_ORIENTATION) {
        /* if the printer supports paper orientation, set it*/
        _devModePointer->dmOrientation = DMORIENT_LANDSCAPE;
        Update();
        bRC = true;
    }
    return bRC;
}

///////////////////////////////////////////////////////////////////////////////
// CDevMode::Update()
//
// We've made one or more changes to the contents of the DEVMODE structure
// that we have a pointer to.
//
// This "in/out" refreshes the contents of the DEVMODE.  Please refer to MS
// KB article Q126897 for more info.
//
///////////////////////////////////////////////////////////////////////////////
void CDevMode::Update()
{
    if (!IsValid())
        return;

    // the following UNICODE goofiness is to fix a c++ compiler error for
    // non-UNICODE builds...when using the /CLR compiler option.
    CString sDeviceName = (TCHAR*) _devModePointer->dmDeviceName;

    const DWORD dwRet = ::DocumentProperties(
        0,
        _printerHandle,
        sDeviceName.GetBuffer(0),
        _devModePointer,       // Use the DEVMODE for "input" and
        _devModePointer,       //      "ouput" buffers
        DM_IN_BUFFER | DM_OUT_BUFFER);

    if (IDOK != dwRet) {
        // ::DocumentProperties() failed.  Get the Win32 error & log it.
        DWORD dwWin32Err = ::GetLastError();
        CString sWin32Err = GetWin32SysErrStr(dwWin32Err);

        CString s;
        s.Format(TEXT("::DocumentProperties(). DeviceName: %s; %s"), sDeviceName, sWin32Err);
        std::cerr << CT2A(s) << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////////
// bool CDevMode::SetDuplex(short nDuplexMode)
///////////////////////////////////////////////////////////////////////////////
bool CDevMode::SetDuplex(short nDuplexMode)
{
    if (!IsValid()) {
        return false;
    }

    // Valid Duplex mode?
    if (nDuplexMode != DMDUP_SIMPLEX    &&
        nDuplexMode != DMDUP_HORIZONTAL  &&
        nDuplexMode != DMDUP_VERTICAL) {
        return false;
    }

    if (_devModePointer->dmFields & DM_DUPLEX) {
        /* if it supports duplex printing, use it */
        _devModePointer->dmDuplex = nDuplexMode;
        Update();
        return true;
    }
    else {
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
// void CDevMode::SetNumCopies()
///////////////////////////////////////////////////////////////////////////////
void CDevMode::SetNumCopies(short NumCopies)
{
    _devModePointer->dmCopies = NumCopies;
    Update();
}

///////////////////////////////////////////////////////////////////////////////
// void CDevMode::IsDuplex()
///////////////////////////////////////////////////////////////////////////////
bool CDevMode::IsDuplex()
{
    return (DMDUP_SIMPLEX != _devModePointer->dmDuplex);
}

CString CDevMode::GetWin32SysErrStr(const DWORD lrc)
{
    const UINT uiSize = 512;
    TCHAR pszMsg[uiSize] = {0};
    DWORD dwSize = ::FormatMessage(
        FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        lrc,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
        pszMsg,
        uiSize,
        NULL);
    if (dwSize > 2) {
        // Take out the trailing CRLF.
        pszMsg[--dwSize] = 0;
        pszMsg[--dwSize] = 0;
    }
    CString result = pszMsg;
    return result;
}