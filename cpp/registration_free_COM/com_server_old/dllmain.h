class Ccom_serverModule : public ATL::CAtlDllModuleT< Ccom_serverModule > {
public:
    DECLARE_LIBID(LIBID_com_serverLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COM_SERVER, "{DCA8BD1A-C95A-47FB-AFB4-B077A689F4D2}")
};

extern class Ccom_serverModule _AtlModule;
