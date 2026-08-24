#include "StdAfx.h"
#include <vector>
#include "Cleaner.h"

const CString SplitChar(L";");

CString GetCleanerKey(const int jobID)
{
   CString cleanerKey;
   cleanerKey.Format(L"cleaner%d", jobID);
   return cleanerKey;
}

std::vector <CString> SplitFilterKeys(const CString filterKeysString)
{
   std::vector <CString> splitFilterKeys;
   CString filterKeys = filterKeysString;
   int currentPosition(0);
   CString splitKey = filterKeys.Tokenize(SplitChar, currentPosition);
   while (!splitKey.IsEmpty()) {
      splitFilterKeys.push_back(splitKey);
      splitKey = filterKeys.Tokenize(SplitChar, currentPosition);
   }
   return splitFilterKeys;
}

CString GetFilterKeysString(PropBag& propBag, const int jobID)
{
   CString filterKeys;
   const CString cleanerKey = GetCleanerKey(jobID);
   CString filterKeysString;
   HRESULT hr = propBag.GetProperty(cleanerKey, filterKeysString);
   if (FAILED(hr)) {
      // logit
   }
   return filterKeysString;
}

void Cleaner::AddFilterKey(PropBag& propBag, const int jobID, CString filterKey)
{
   CString filterKeysString = GetFilterKeysString(propBag, jobID);
   filterKeysString = filterKeysString + CString(filterKey) + CString(SplitChar);
   CString cleanerKey = GetCleanerKey(jobID);
   BOOL rc = propBag.DeleteProperty(cleanerKey);
   HRESULT hr = propBag.AddProperty(cleanerKey, filterKeysString);
}

void Cleaner::Clean(PropBag& propBag, const int jobID)
{
   CString filterKeysString = GetFilterKeysString(propBag, jobID);
   if (filterKeysString.IsEmpty()) return;

   std::vector <CString> filterKeys = SplitFilterKeys(filterKeysString);
   for (size_t filterKeyIndex = 0; filterKeyIndex < filterKeys.size(); filterKeyIndex++) {
      CString keyToDelete = filterKeys[filterKeyIndex];
      propBag.DeleteProperty(keyToDelete);
   }

   CString cleanerKey = GetCleanerKey(jobID);
   propBag.DeleteProperty(cleanerKey);
}