#include "stdafx.h"
#include <iostream>
#include <atlbase.h>
#include <atlstr.h>
#include "PropBag.h"
#include "Cleaner.h"

int _tmain(int argc, _TCHAR* argv[])
{
   PropBag propBag;

   CString val1 = L"value 1";
   CString job01key = L"job key one";

   HRESULT hr = propBag.AddProperty(job01key, val1);
   ATLASSERT(S_OK == hr);

   hr = propBag.AddProperty(job01key, val1);
   ATLASSERT(E_INVALIDARG == hr);

   BOOL rc = propBag.DeleteProperty(job01key);
   ATLASSERT(rc);

   rc = propBag.DeleteProperty(job01key);
   ATLASSERT(!rc);

   rc = propBag.DeleteProperty(job01key);
   ATLASSERT(!rc);

   hr = propBag.AddProperty(job01key, val1);
   ATLASSERT(S_OK == hr);

   Cleaner::AddFilterKey(propBag, 1, job01key);

   CString job02key = L"job key 2";
   CString val2 = L"value 2";
   hr = propBag.AddProperty(job02key, val2);
   ATLASSERT(S_OK == hr);

   Cleaner::AddFilterKey(propBag, 2, job02key);

   hr = propBag.AddProperty(L"another job1 key", L"another job1 value");
   ATLASSERT(S_OK == hr);
   Cleaner::AddFilterKey(propBag, 1, L"another job1 key");

   Cleaner::Clean(propBag, 2);
   Cleaner::Clean(propBag, 1);

   std::cout << std::endl << "press any key";
   getchar();

   return 0;
}