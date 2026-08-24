#include "precomp.hxx"
#include "oem.hxx"
#include "debug.hxx"
#include "globals.hxx"

// This indicates to Prefast that this is a usermode driver file.
_Analysis_mode_(_Analysis_code_type_user_driver_);

BOOL WINAPI DllMain(HINSTANCE hInst, WORD wReason, LPVOID)
{
    switch (wReason) {
    case DLL_PROCESS_ATTACH:
        VERBOSE(DLLTEXT("Process attach.\r\n"));
        ghInstance = hInst;
        break;

    case DLL_THREAD_ATTACH:
        VERBOSE(DLLTEXT("Thread attach.\r\n"));
        break;

    case DLL_PROCESS_DETACH:
        VERBOSE(DLLTEXT("Process detach.\r\n"));
        break;

    case DLL_THREAD_DETACH:
        VERBOSE(DLLTEXT("Thread detach.\r\n"));
        break;
    }

    return TRUE;
}