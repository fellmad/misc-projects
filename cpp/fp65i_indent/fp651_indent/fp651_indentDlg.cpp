#include "stdafx.h"
#include <WinSpool.h>
#include <string>
#include "ICE_API.h"
#include "fp651_indent.h"
#include "fp651_indentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

const CString PersistSectionName(TEXT("Settings"));
const CString PersistIndentTextName(TEXT("IndentText"));
const CString PersistIndentPositionName(TEXT("IndentPosition"));

BEGIN_MESSAGE_MAP(Cfp651_indentDlg, CDialog)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   //}}AFX_MSG_MAP
   ON_BN_CLICKED(IDC_print_button, &Cfp651_indentDlg::OnBnClickedprintbutton)
   ON_WM_DESTROY()
END_MESSAGE_MAP()

Cfp651_indentDlg::Cfp651_indentDlg(CWnd* pParent /*=NULL*/)
: CDialog(Cfp651_indentDlg::IDD, pParent)
, _indentText(TEXT("777"))
, _xPosition(2280)
, _numCopies(1)
{
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cfp651_indentDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_indentTextEditBox, _indentText);
   DDX_Text(pDX, IDC_xPositionTextEditBox, _xPosition);
   DDV_MinMaxInt(pDX, _xPosition, 0, 4000);
   DDX_Control(pDX, IDC_printername_combo, _printerNameCombo);
   DDX_Text(pDX, IDC_numCopiesEditBox, _numCopies);
   DDV_MinMaxInt(pDX, _numCopies, 1, 100);
}

BOOL Cfp651_indentDlg::OnInitDialog()
{
   _xPosition = AfxGetApp()->GetProfileInt(PersistSectionName, PersistIndentPositionName, _xPosition);
   _indentText = AfxGetApp()->GetProfileString(PersistSectionName, PersistIndentTextName, _indentText);

   CDialog::OnInitDialog();

   SetIcon(m_hIcon, TRUE);
   SetIcon(m_hIcon, FALSE);

   LoadPrinterNameCombo();

   return true;
}

void Cfp651_indentDlg::OnPaint()
{
   if (IsIconic()) {
      CPaintDC dc(this); // device context for painting
      SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
      int cxIcon = GetSystemMetrics(SM_CXICON);
      int cyIcon = GetSystemMetrics(SM_CYICON);
      CRect rect;
      GetClientRect(&rect);
      int x = (rect.Width() - cxIcon + 1) / 2;
      int y = (rect.Height() - cyIcon + 1) / 2;
      dc.DrawIcon(x, y, m_hIcon);
   }
   else {
      CDialog::OnPaint();
   }
}

HCURSOR Cfp651_indentDlg::OnQueryDragIcon()
{
   return static_cast <HCURSOR> (m_hIcon);
}

void Cfp651_indentDlg::LoadPrinterNameCombo()
{
   DWORD bytesNeeded(0);
   DWORD bytesReturned(0);
   ::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 2, NULL, 0, &bytesNeeded, &bytesReturned);

   CTempBuffer <byte> buf(bytesNeeded);
   DWORD numPrinters(0);
   if (::EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 2, buf, bytesNeeded, &bytesNeeded, &numPrinters))
   {
      _printerNameCombo.Clear();
      PRINTER_INFO_2* printerInfoList = (PRINTER_INFO_2*) &buf[0];
      for (DWORD printerIndex = 0; printerIndex < numPrinters; printerIndex++) {
         const CString printerName = printerInfoList[printerIndex].pPrinterName;
         _printerNameCombo.AddString(printerName);
      }
   }
   _printerNameCombo.SetCurSel(0);
}

void Cfp651_indentDlg::UnTopcoatEntirePage(HDC hdc)
{
   CString errmsg;

   int savedDC = ::SaveDC(hdc);

   int rc = ::SetTopCoatMode(hdc, true);
   if (!rc) {
      errmsg.Format(TEXT("::SetTopCoatMode() fail %08x"), ::GetLastError());
      throw runtime_error(string(errmsg.GetBuffer()));
   }

   const int widthPixels = ::GetDeviceCaps(hdc, HORZRES);
   const int heightPixels = ::GetDeviceCaps(hdc, VERTRES); 

   RECT rect = {0};
   rect.right = widthPixels;
   rect.bottom = heightPixels;

   rc = ::FillRect(hdc, &rect, (HBRUSH) ::GetStockObject(TOP_COAT_OFF_BRUSH));
   if (!rc) {
      errmsg.Format(TEXT("::FillRect() fail %08x"), ::GetLastError());
      throw runtime_error(string(errmsg.GetBuffer()));
   }

   rc = ::SetTopCoatMode(hdc, false);
   if (!rc) {
      errmsg.Format(TEXT("::SetTopCoatMode() fail %08x"), ::GetLastError());
      throw runtime_error(string(errmsg.GetBuffer()));
   }

   ::RestoreDC(hdc, savedDC);
   if (!rc) {
      errmsg.Format(TEXT("::RestoreDC() fail %08x"), ::GetLastError());
      throw runtime_error(string(errmsg.GetBuffer()));
   }
}

void Cfp651_indentDlg::OnBnClickedprintbutton()
{
   UpdateData(true);

   CString errmsg;
   CString printerName;
   _printerNameCombo.GetWindowText(printerName);

   CWaitCursor wait;

   for (int copyIndex = 0; copyIndex < _numCopies; copyIndex++)
   {
      try 
      {
         const int indentStatus = ::GetCardPrinterIndenterStatus(printerName.GetBuffer());
         if (1 != indentStatus) {
            errmsg.Format(TEXT("::GetCardPrinterIndenterStatus(%s) fail; indenter not installed"), printerName);
            throw runtime_error(string(errmsg.GetBuffer()));
         }

         HDC hdc = ::CreateDC(NULL, printerName, NULL, NULL);
         if (NULL == hdc) {
            errmsg.Format(TEXT("::CreateDC(%s): %08x"), printerName, ::GetLastError());
            throw runtime_error(string(errmsg.GetBuffer()));
         }

         DOCINFO docinfo = {0};
         docinfo.cbSize = sizeof docinfo;
         docinfo.lpszDocName = TEXT("indent only");

         int rc = ::StartDoc(hdc, &docinfo);
         if (rc <= 0) {
            errmsg.Format(TEXT("::StartDoc()"), ::GetLastError());
            throw runtime_error(string(errmsg.GetBuffer()));
         }

         rc = ::StartPage(hdc);
         if (rc <= 0) {
            errmsg.Format(TEXT("::StartPage() %08x"), ::GetLastError());
            throw runtime_error(string(errmsg.GetBuffer()));
         }

         UnTopcoatEntirePage(hdc);

         INDENT_TRACK indentData = {0};
         indentData.Xlocation = _xPosition;
         indentData.length = _indentText.GetLength() + 1;
         ::strcpy_s((PCHAR) indentData.pindentData, sizeof indentData.pindentData, CT2A(_indentText));

         rc = ::SendIndentData(hdc, &indentData);

         rc = ::EndPage(hdc);
         if (rc <= 0) {
            errmsg.Format(TEXT("::EndPage()"), ::GetLastError());
            throw runtime_error(string(errmsg.GetBuffer()));
         }

         rc = ::EndDoc(hdc);
         if (rc <= 0) {
            errmsg.Format(TEXT("::EndDoc()"), ::GetLastError());
            throw runtime_error(string(errmsg.GetBuffer()));
         }

         ::DeleteDC(hdc);
      }
      catch (runtime_error& e) {
         ::AfxMessageBox(e.what(), MB_OK | MB_ICONERROR);
         return;
      }
   }
}

void Cfp651_indentDlg::OnDestroy()
{
   AfxGetApp()->WriteProfileInt(PersistSectionName, PersistIndentPositionName, _xPosition);
   AfxGetApp()->WriteProfileString(PersistSectionName, PersistIndentTextName, _indentText);

   CDialog::OnDestroy();
}
