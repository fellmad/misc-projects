#include "stdafx.h"
#include <iostream>

void enum_PrintProcessorDatatypes(TCHAR* processorName)
{
   DWORD bytesNeeded(0);
   DWORD structureCount(0);
   BOOL rc = ::EnumPrintProcessorDatatypes(
      NULL,
      processorName,
      1,
      NULL,
      0,
      &bytesNeeded,
      &structureCount);

   DATATYPES_INFO_1* datatypes_info_1s = (DATATYPES_INFO_1*) new BYTE[bytesNeeded];

   rc = ::EnumPrintProcessorDatatypes(
      NULL,
      processorName,
      1,
      (PBYTE) datatypes_info_1s,
      bytesNeeded,
      &bytesNeeded,
      &structureCount);

   for (DWORD i = 0; i < structureCount; i++)
   {
      std::cout << "   " << CW2A(datatypes_info_1s[i].pName) << std::endl;
   }

   delete [] datatypes_info_1s;
}

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
   DWORD bytesNeeded(0);
   DWORD structureCount(0);
   BOOL rc = ::EnumPrintProcessors(
      NULL,
      NULL,
      1,
      NULL,
      0,
      &bytesNeeded,
      &structureCount);

   PRINTPROCESSOR_INFO_1* printProcessor_info_1s = (PRINTPROCESSOR_INFO_1*) new BYTE[bytesNeeded];

   rc = ::EnumPrintProcessors(
      NULL,
      NULL,
      1,
      (PBYTE) printProcessor_info_1s,
      bytesNeeded,
      &bytesNeeded,
      &structureCount);

   for (DWORD i = 0; i < structureCount; i++)
   {
      std::cout << CW2A(printProcessor_info_1s[i].pName) << std::endl;
      enum_PrintProcessorDatatypes(printProcessor_info_1s[i].pName);
   }

   delete [] printProcessor_info_1s;

   return 0;
}
