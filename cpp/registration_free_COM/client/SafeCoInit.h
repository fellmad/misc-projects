#include <Objbase.h>
#include <iostream>

class SafeCoInit {
public:
    SafeCoInit() : m_doCoUninitialize(FALSE)
    {
        HRESULT hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);

        if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) {
            std::cerr << "CoInitializeEx(): " << std::hex << hr << std::endl;
        }
        else if (SUCCEEDED(hr)) {
            m_doCoUninitialize = TRUE;
        }
    }

    ~SafeCoInit()
    {
        if (m_doCoUninitialize) {
            ::CoUninitialize();
        }
    }

private:

    SafeCoInit(SafeCoInit const&);
    SafeCoInit& operator=(SafeCoInit const&);
    BOOL m_doCoUninitialize;
};
