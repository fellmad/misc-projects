// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the WIN32DLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// WIN32DLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef WIN32DLL_EXPORTS
#define WIN32DLL_API __declspec(dllexport)
#else
#define WIN32DLL_API __declspec(dllimport)
#endif

// This class is exported from the win32dll.dll
class WIN32DLL_API Cwin32dll {
public:
    Cwin32dll(void);
    // TODO: add your methods here.
};

extern WIN32DLL_API int nwin32dll;

WIN32DLL_API int IsWindows10(void);
