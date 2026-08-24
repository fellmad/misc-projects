#include "stdafx.h"
#include <winspool.h>
#include <atlcoll.h>
#include "enumPrintJobs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

using namespace std;

typedef CAtlList <JOB_INFO_2> JobInfo2List;

PBYTE ji2Buf(NULL);

void usage(TCHAR* argv[])
{
   cout << "usage: " << CT2A(argv[0]) << " <printername>" << endl;
}

////////////////////////////////////////////////////////////////////////////////
// FormatJobInfo2List()
////////////////////////////////////////////////////////////////////////////////
CString FormatJobInfo2List(JobInfo2List& ji2List)
{
   CString s;
   CString s2;
   for (POSITION pos = ji2List.GetHeadPosition(); pos;)
   {
      JOB_INFO_2 ji2 = ji2List.GetNext(pos);
      s2.Format(TEXT("%ls %8ld %-16ls %02ld:%02ld:%02ld:%02ld\n"),
         ji2.pPrinterName,
         ji2.JobId,
         ji2.pDocument,
         ji2.Submitted.wHour,
         ji2.Submitted.wMinute,
         ji2.Submitted.wSecond,
         ji2.Submitted.wMilliseconds);
      s += s2;
   }
   s += CString(TEXT("\n"));
   return s;
}

////////////////////////////////////////////////////////////////////////////////
// EnumJobInfo2()
////////////////////////////////////////////////////////////////////////////////
void EnumJobInfo2(HANDLE printerHandle, JobInfo2List& ji2List)
{
   DWORD bytesNeeded(0);
   DWORD jobReturned(0);
   ji2List.RemoveAll();

   if (ji2Buf)
   {
      delete [] ji2Buf;
   }

   do
   {
      // call it just to get the buffer size into bytesNeeded:
      BOOL brc = ::EnumJobs(
         printerHandle,
         0,             // index of first job
         10000,         // number of jobs to enumerate
         2,             // information level
         NULL,          // job information buffer
         0,             // size of job information buffer
         &bytesNeeded,  // bytes received or required
         &jobReturned); // number of jobs received

      if (bytesNeeded)
      {
         ji2Buf = new BYTE[bytesNeeded];
         brc = ::EnumJobs(
            printerHandle,
            0,             // index of first job
            10000,         // number of jobs to enumerate
            2,             // information level
            ji2Buf,        // job information buffer
            bytesNeeded,   // size of job information buffer
            &bytesNeeded,  // bytes received or required
            &jobReturned); // number of jobs received
         if (!brc)
         {
            cout << CW2A(TEXT("EnumJobs() ")) << ::GetLastError() << endl;
            break;
         }

         for (DWORD jobndx = 0; jobndx < jobReturned; jobndx++)
         {
            JOB_INFO_2* pji2 = (JOB_INFO_2*) (ji2Buf + (jobndx * sizeof JOB_INFO_2));
            ji2List.AddTail(*pji2);
         }
      }
      else
      {
         const DWORD dw = ::GetLastError();
         if (ERROR_INSUFFICIENT_BUFFER != dw)
         {
            cout << CW2A(TEXT("EnumJobs() ")) << ::GetLastError() << endl;
            break;
         }
      }
   } while (false);
}

////////////////////////////////////////////////////////////////////////////////
// main()
////////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, TCHAR* argv[], TCHAR* /*envp[]*/)
{
   int nRetCode = 0;
   do
   {
      if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
      {
         _tprintf(_T("Fatal Error: MFC initialization failed\n"));
         nRetCode = 1;
         break;
      }

      if (argc < 2)
      {
         usage(argv);
         break;
      }

      //BOOL brc = ::SetConsoleCtrlHandler(NULL, true);
      //if(!brc)
      //{
      //   cout << CW2A(TEXT("SetConsoleCtrlHandler() ")) << ::GetLastError() << endl;
      //   break;
      //}

      const CString printerName = argv[1];
      HANDLE hPrinter(0);
      BOOL brc = ::OpenPrinter(CT2W(printerName), &hPrinter, NULL);
      if (!brc)
      {
         cout << CW2A(TEXT("OpenPrinter() ")) << ::GetLastError() << endl;
         break;
      }

      do
      {
         JobInfo2List ji2List;
         EnumJobInfo2(hPrinter, ji2List);
         CString s = FormatJobInfo2List(ji2List);
         cout << CT2A(s);

         HANDLE hChange = ::FindFirstPrinterChangeNotification(
            hPrinter,            // handle to printer
            PRINTER_CHANGE_ALL,  // conditions to monitor
            0,                   // reserved, must be zero
            NULL);               // fields to monitor

         ::WaitForSingleObject(hChange, 100000);
         ::FindClosePrinterChangeNotification(hChange);
      } while (true);

   } while (false);

   if (ji2Buf)
   {
      delete [] ji2Buf;
   }

   return nRetCode;
}
