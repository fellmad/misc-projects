// dllmain.h : Declaration of module class.

class Ccom_serverModule : public ATL::CAtlDllModuleT< Ccom_serverModule > {
public:
    DECLARE_LIBID(LIBID_com_serverLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COM_SERVER, "{BDB0C4C0-C33C-46C2-B9DC-ACF03D7BEDAC}")
};

extern class Ccom_serverModule _AtlModule;
