#include "stdafx.h"
#include "fp651_indent.h"
#include "fp651_indentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(Cfp651_indentApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

Cfp651_indentApp::Cfp651_indentApp()
{
}

Cfp651_indentApp theApp;

BOOL Cfp651_indentApp::InitInstance()
{
	CWinAppEx::InitInstance();

	SetRegistryKey(_T("Datacard"));

	Cfp651_indentDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
	}
	else if (nResponse == IDCANCEL) {
	}

	return false;
}
