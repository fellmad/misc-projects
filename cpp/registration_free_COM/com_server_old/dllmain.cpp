#include "stdafx.h"
#include "resource.h"
#include "com_server_i.h"
#include "dllmain.h"

Ccom_serverModule _AtlModule;

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}