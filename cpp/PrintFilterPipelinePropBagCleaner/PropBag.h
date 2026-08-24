#pragma once

#include <atlbase.h>
#include <atlstr.h>
#include <map>

class PropBag
{
public:

   virtual HRESULT  AddProperty(CString name, CString val);
   virtual HRESULT  GetProperty(CString name, CString& value);
   virtual BOOL     DeleteProperty(CString name);

private:

   void Dump();

   typedef std::map <CString, CString> StringStringMap;
   StringStringMap _map;
};
