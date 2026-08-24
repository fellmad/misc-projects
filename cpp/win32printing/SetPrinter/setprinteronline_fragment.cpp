void SetPrinterOnline(const CString printerName)
{
    stringstream exceptionText;

    HANDLE printerHandle {};
    PRINTER_DEFAULTS defaults {};
    defaults.DesiredAccess = PRINTER_ALL_ACCESS;
    int rc = ::OpenPrinterW(CT2W(printerName), &printerHandle, &defaults);
    if (0 == rc) {
        const auto lastError = ::GetLastError();
        exceptionText << "OpenPrinterW(): " << " 0x" << hex << lastError << " " << CW2A(util::Win32ErrorString(lastError));
        throw runtime_error(exceptionText.str());
    }

    DWORD needed {};
    rc = ::GetPrinterW(printerHandle, 2, nullptr, 0, &needed);
    auto lastError = ::GetLastError();
    if (!(0 == rc && ERROR_INSUFFICIENT_BUFFER == lastError)) {
        const auto lastError = ::GetLastError();
        exceptionText << "GetPrinterW(): " << " 0x" << hex << lastError << " " << CW2A(util::Win32ErrorString(lastError));
        throw runtime_error(exceptionText.str());
    }

    std::vector <byte> printerInfo2Bytes(needed);

    DWORD returned {};
    rc = ::GetPrinterW(printerHandle, 2, &printerInfo2Bytes[0], needed, &returned);
    lastError = ::GetLastError();
    if (0 == rc) {
        const auto lastError = ::GetLastError();
        exceptionText << "GetPrinterW(): " << " 0x" << hex << lastError << " " << CW2A(util::Win32ErrorString(lastError));
        throw runtime_error(exceptionText.str());
    }

    const auto printer_info_2 = (PRINTER_INFO_2*) &printerInfo2Bytes[0];
    if (PRINTER_STATUS_OFFLINE & printer_info_2->Status) {
        DWORD newStatus = 0;
        rc = ::SetPrinterW(printerHandle, 0, (PBYTE) newStatus, PRINTER_CONTROL_SET_STATUS);
        if (0 == rc) {
            const auto lastError = ::GetLastError();
            exceptionText << "SetPrinterW(): " << " 0x" << hex << lastError << " " << CW2A(util::Win32ErrorString(lastError));
            throw runtime_error(exceptionText.str());
        }
    }
}