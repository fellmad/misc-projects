#pragma once

struct CDevMode {
private:

    HANDLE _printerHandle;

private:

    CDevMode()
    {
    };                          // make default c'tor private
    CDevMode(const CDevMode&)
    {
    };         // don't allow copying
    CDevMode& operator=(const CDevMode&)    // don't allow assignment
    {
        return(*this);
    };

    void Update();

public:

    LPDEVMODE _devModePointer;
    HANDLE GetHandle() const {return _printerHandle;}

public:

    CDevMode(CString printerName);
    ~CDevMode();

    bool IsValid();
    bool IsDuplex();
    bool SetPortrait();
    bool SetLandScape();
    bool SetDuplex(short nDuplexMode);
    void SetNumCopies(short NumCopies);

    static CString GetWin32SysErrStr(const DWORD lrc);
};
