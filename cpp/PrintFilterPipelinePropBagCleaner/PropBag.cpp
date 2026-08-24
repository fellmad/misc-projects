#include "stdafx.h"
#include "PropBag.h"
#include <iostream>

#define E_ELEMENT_NOT_FOUND  HRESULT_FROM_WIN32(ERROR_NOT_FOUND)

void PropBag::Dump()
{
   std::cout << "start dump -" << std::endl;
   StringStringMap::iterator iter;
   for (iter = _map.begin(); iter != _map.end(); iter++) {
      CString key = iter->first;
      CString value = iter->second;
      std::wcout << L"  " << key.GetBuffer() << L"; " << value.GetBuffer() << std::endl;
   }
   std::cout << "end dump ---" << std::endl;
}

HRESULT PropBag::AddProperty(CString name, CString value)
{
   Dump();

   // simulate 'duplicate entry' behavior:
   StringStringMap::iterator iter = _map.find(name);
   if (_map.end() != iter) {
      return E_INVALIDARG;
   }

   _map[name] = value;

   Dump();

   return S_OK;
}

HRESULT PropBag::GetProperty(CString name, CString& value)
{
   Dump();

   StringStringMap::iterator iter = _map.find(name);
   if (_map.end() == iter) {
      return E_ELEMENT_NOT_FOUND;
   }

   value = _map[name];

   Dump();

   return S_OK;
}

BOOL PropBag::DeleteProperty(CString name)
{
   Dump();

   StringStringMap::iterator iter = _map.find(name);
   if (_map.end() == iter) {
      return false;
   }

   _map.erase(iter);

   Dump();

   return true;
}
