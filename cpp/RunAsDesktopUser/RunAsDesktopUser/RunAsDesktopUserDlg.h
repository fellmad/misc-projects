#pragma once
#include "afxwin.h"

class CRunAsDesktopUserDlg : public CDialog
{
public:
    CRunAsDesktopUserDlg(CWnd* pParent = NULL);	// standard constructor

    enum { IDD = IDD_RUNASDESKTOPUSER_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
private:
    CString m_sApp;
    CString m_sCmdLine;
    CString m_sCurrDir;

    afx_msg void OnBnClickedRun();
};