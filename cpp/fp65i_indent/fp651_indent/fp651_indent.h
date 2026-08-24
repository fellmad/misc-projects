#pragma once

#ifndef __AFXWIN_H__
   #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

class Cfp651_indentApp : public CWinAppEx
{
public:
   Cfp651_indentApp();

public:
   virtual BOOL InitInstance();

   DECLARE_MESSAGE_MAP();
};

extern Cfp651_indentApp theApp;