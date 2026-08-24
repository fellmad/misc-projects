#pragma once

class Cfp651_indentDlg : public CDialog
{
public:

   Cfp651_indentDlg(CWnd* pParent = NULL);
   enum { IDD = IDD_FP651_INDENT_DIALOG };

private:

   virtual void DoDataExchange(CDataExchange* pDX);
   virtual BOOL OnInitDialog();

   DECLARE_MESSAGE_MAP();

   HICON m_hIcon;

   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnBnClickedprintbutton();
   afx_msg void OnDestroy();

   int _xPosition;
   CString _indentText;
   CComboBox _printerNameCombo;
   int _numCopies;

   void LoadPrinterNameCombo();
   void UnTopcoatEntirePage( HDC hdc );
};
