#include "stdafx.h"
#include <WinSpool.h>
#include <atlstr.h>
#include <atlcoll.h>
#include <iostream>

//MONITOR_INFO_2
//The MONITOR_INFO_2 structure identifies a monitor. 
//
//typedef struct _MONITOR_INFO_2 { 
//   LPTSTR pName; 
//   LPTSTR pEnvironment; 
//   LPTSTR pDLLName; 
//} MONITOR_INFO_2, *PMONITOR_INFO_2; 
//Members

struct MonitorInfo2 {
   CString _name;
   CString _environment;
   CString _dllname;
};

typedef CAtlList <MonitorInfo2> MonitorInfo2List;

void PrintMonitorInfo2s(MonitorInfo2List& MonitorInfo2s) {
   std::cout << "MONITOR_INFO_2:" << std::endl;

   for (POSITION pos = MonitorInfo2s.GetHeadPosition(); NULL != pos;) {
      MonitorInfo2 MonitorInfo2 = MonitorInfo2s.GetNext(pos);
      std::cout << "  " << CT2A(MonitorInfo2._name) << std::endl;
      std::cout << "    " << CT2A(MonitorInfo2._environment) << std::endl;
      std::cout << "    " << CT2A(MonitorInfo2._dllname) << std::endl;
   }
}


int _tmain(int argc, _TCHAR* argv[])
{
   UNREFERENCED_PARAMETER(argc);
   UNREFERENCED_PARAMETER(argv);

   DWORD needed(0);
   DWORD returned(0);
   BOOL brc = ::EnumMonitors(NULL, 2, NULL, 0, &needed, &returned);

   MONITOR_INFO_2* monitor_into_2s = (MONITOR_INFO_2*) new BYTE[needed];
   brc = ::EnumMonitors(NULL, 2, (PBYTE) monitor_into_2s, needed, &needed, &returned);

   MonitorInfo2List monitorInfo2s;

   for (int i = 0; i < (int) returned; i++) {
      MonitorInfo2 monitorInfo2;
      monitorInfo2._name = monitor_into_2s[i].pName;
      monitorInfo2._dllname = monitor_into_2s[i].pDLLName;
      monitorInfo2._environment = monitor_into_2s[i].pEnvironment;
      monitorInfo2s.AddTail(monitorInfo2);
   }

   PrintMonitorInfo2s(monitorInfo2s);
   return 0;
}
