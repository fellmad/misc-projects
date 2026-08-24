#pragma once
#include "PropBag.h"

class Cleaner
{
public:

   static void AddFilterKey(PropBag& probBag, const int jobID, CString filterKey);
   static void Clean(PropBag& propBag, const int jobID);
};