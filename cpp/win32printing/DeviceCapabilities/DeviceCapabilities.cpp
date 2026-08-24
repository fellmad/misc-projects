#include <SDKDDKVer.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <atlstr.h>
#include <map>

using IntWStringMap = std::map<int, std::wstring>;

IntWStringMap loadCapabilityNamesMap()
{
    IntWStringMap capabilities;

    capabilities[DC_BINADJUST] = L"DC_BINADJUST";
    capabilities[DC_BINNAMES] = L"DC_BINNAMES";
    capabilities[DC_BINS] = L"DC_BINS";
    capabilities[DC_COLLATE] = L"DC_COLLATE";
    capabilities[DC_COLORDEVICE] = L"DC_COLORDEVICE";
    capabilities[DC_COPIES] = L"DC_COPIES";
    capabilities[DC_DATATYPE_PRODUCED] = L"DC_DATATYPE_PRODUCED";
    capabilities[DC_DRIVER] = L"DC_DRIVER";
    capabilities[DC_DUPLEX] = L"DC_DUPLEX";
    capabilities[DC_EMF_COMPLIANT] = L"DC_EMF_COMPLIANT";
    capabilities[DC_ENUMRESOLUTIONS] = L"DC_ENUMRESOLUTIONS";
    capabilities[DC_EXTRA] = L"DC_EXTRA";
    capabilities[DC_FIELDS] = L"DC_FIELDS";
    capabilities[DC_FILEDEPENDENCIES] = L"DC_FILEDEPENDENCIES";
    capabilities[DC_MANUFACTURER] = L"DC_MANUFACTURER";
    capabilities[DC_MAXEXTENT] = L"DC_MAXEXTENT";
    capabilities[DC_MEDIAREADY] = L"DC_MEDIAREADY";
    capabilities[DC_MEDIATYPENAMES] = L"DC_MEDIATYPENAMES";
    capabilities[DC_MEDIATYPES] = L"DC_MEDIATYPES";
    capabilities[DC_MINEXTENT] = L"DC_MINEXTENT";
    capabilities[DC_MODEL] = L"DC_MODEL";
    capabilities[DC_NUP] = L"DC_NUP";
    capabilities[DC_ORIENTATION] = L"DC_ORIENTATION";
    capabilities[DC_PAPERNAMES] = L"DC_PAPERNAMES";
    capabilities[DC_PAPERS] = L"DC_PAPERS";
    capabilities[DC_PAPERSIZE] = L"DC_PAPERSIZE";
    capabilities[DC_PERSONALITY] = L"DC_PERSONALITY";
    capabilities[DC_PRINTERMEM] = L"DC_PRINTERMEM";
    capabilities[DC_PRINTRATE] = L"DC_PRINTRATE";
    capabilities[DC_PRINTRATEPPM] = L"DC_PRINTRATEPPM";
    capabilities[DC_PRINTRATEUNIT] = L"DC_PRINTRATEUNIT";
    capabilities[DC_SIZE] = L"DC_SIZE";
    capabilities[DC_STAPLE] = L"DC_STAPLE";
    capabilities[DC_TRUETYPE] = L"DC_TRUETYPE";
    capabilities[DC_VERSION] = L"DC_VERSION";

    return capabilities;
}

std::wstring decode_capability_result(const int capability, const int devCapResult, wchar_t* cap_chars)
{
    std::wstring decoded;
    std::wstringstream formatted_stream;

    switch (capability) {
    case DC_MODEL: decoded = cap_chars; break;
    case DC_DRIVER: {
        formatted_stream << std::hex;
        formatted_stream << devCapResult;
        decoded = formatted_stream.str();
        break;
    }
    case DC_PAPERNAMES: {
        for (int paperNameIndex = 0; paperNameIndex < devCapResult; paperNameIndex++) {
            auto paperNameChars = cap_chars + 64 * paperNameIndex;
            std::wstring paperName(paperNameChars);
            formatted_stream << "  " << paperName << std::endl;
        }
        decoded = formatted_stream.str();
        break;
    }

    case DC_VERSION: {
        formatted_stream << std::hex;
        formatted_stream << devCapResult;
        decoded = formatted_stream.str();
        break;
    }
    }
    return decoded;
}

void usage()
{
    std::wcout << "printername required." << std::endl;
    ::exit(-1);
}

int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
    if (argc < 2) usage();
    std::wstring printername = argv[1];

    HANDLE printerHandle{};
    auto openPrinterResult = ::OpenPrinterW(CW2T(printername.c_str()), &printerHandle, nullptr);
    if (!openPrinterResult) {
        std::wcout << "error " << ::GetLastError() << " opening " << printername << std::endl;
    }
    if (printerHandle) ::ClosePrinter(printerHandle);

    std::wcout << printername << std::endl;

    wchar_t pwchars[1024 * 256]{};
    const auto sizeof_pwchars_in_bytes = sizeof pwchars;

    auto capabilities_name_map = loadCapabilityNamesMap();
    auto it = IntWStringMap::iterator();
    for (const auto& cap : capabilities_name_map) {
        const auto capability_number = cap.first;
        const int result = ::DeviceCapabilitiesW(
            printername.c_str(),
            nullptr,
            capability_number,
            pwchars,
            nullptr);
        if (result > 0) {
            std::wcout << cap.first << ", " << cap.second << std::endl;
            auto decoded = decode_capability_result(capability_number, result, pwchars);
            if (decoded.length()) {
                std::wcout << "  " << decoded << std::endl;
            }
        }
        ::memset(pwchars, 0, sizeof_pwchars_in_bytes);
    }
}