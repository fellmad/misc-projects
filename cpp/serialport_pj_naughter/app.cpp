/////////////////////////////////  Includes  //////////////////////////////////

#include "stdafx.h"
#include "SerialPort.h"


///////////////////////////////// Defines /////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////// Implementation ///////////////////////////////

class CSerialPortApp : public CWinApp
{
public:
  virtual BOOL InitInstance();
};

CSerialPortApp theApp;

BOOL CSerialPortApp::InitInstance()
{
  BYTE* pBuf = new BYTE[10000];

  try
  {
    COMMCONFIG config;
    CSerialPort::GetDefaultConfig(1, config);

    CSerialPort port;
    port.Open(1, 1200, CSerialPort::NoParity, 8, CSerialPort::OneStopBit, CSerialPort::XonXoffFlowControl);

    HANDLE hPort = port.Detach();
    port.Attach(hPort);

    DWORD dwModemStatus;
    port.GetModemStatus(dwModemStatus);

    DCB dcb;
    port.GetState(dcb);

    dcb.BaudRate = 9600;
    port.SetState(dcb);    

    DWORD dwErrors;                      
    port.ClearError(dwErrors);

    port.SetBreak();
    port.ClearBreak();

    COMSTAT stat;
    port.GetStatus(stat);

    DWORD dwBytesWaiting = port.BytesWaiting();
    dwBytesWaiting;

    COMMTIMEOUTS timeouts;
    port.GetTimeouts(timeouts);

    port.Setup(10000, 10000);

    port.GetConfig(config);

    config.dcb.BaudRate = 9600;
    port.SetConfig(config);

    port.Set0WriteTimeout();
    port.Set0ReadTimeout();

    char sBuf[] = "This should appear on the serial port";
    port.Write(sBuf, static_cast<DWORD>(strlen(sBuf)));

    DWORD dwMask;
    port.GetMask(dwMask);

    port.SetMask(EV_TXEMPTY); 

    //port.WaitEvent(dwMask);

    port.TerminateOutstandingWrites();

    port.TransmitChar('p');

    port.Set0Timeout();

    char sRxBuf[10];
    DWORD dwRead = port.Read(sRxBuf, 10);
    dwRead; //To remove unreferrenced variable in VC 6.

    port.TerminateOutstandingReads();

    port.ClearDTR();

    port.ClearRTS();

    port.SetDTR();

    port.SetRTS();

    port.SetXOFF();

    port.SetXON();

    COMMPROP properties;
    port.GetProperties(properties);

    port.ClearWriteBuffer();

    port.ClearReadBuffer();

    port.Flush();

    port.Close();


    //Try out the overlapped functions
    CSerialPort port2;
    port2.Open(1, 9600, CSerialPort::NoParity, 8, CSerialPort::OneStopBit, CSerialPort::XonXoffFlowControl, TRUE);

    CEvent event(FALSE, TRUE);
    OVERLAPPED overlapped;
    memset(&overlapped, 0, sizeof(overlapped));
    overlapped.hEvent = event;
    try
    {
      port2.Write(pBuf, 10000, overlapped);
    }
    catch(CSerialException* pEx)
    {
      if (pEx->m_dwError == ERROR_IO_PENDING)
      {
        DWORD dwBytesTransferred = 0;
        port2.GetOverlappedResult(overlapped, dwBytesTransferred, TRUE);
        pEx->Delete();
      }
      else
      {
        DWORD dwError = pEx->m_dwError;
        pEx->Delete();
        CSerialPort::ThrowSerialException(dwError);
      }
    }
    try
    {
      port2.Read(pBuf, 10, overlapped);
    }
    catch(CSerialException* pEx)
    {
      if (pEx->m_dwError == ERROR_IO_PENDING)
      {
        DWORD dwBytesTransferred = 0;
        port2.GetOverlappedResult(overlapped, dwBytesTransferred, TRUE);
        pEx->Delete();
      }
      else
      {
        DWORD dwError = pEx->m_dwError;
        pEx->Delete();
        CSerialPort::ThrowSerialException(dwError);
      }
    }
          
    port2.SetMask(EV_TXEMPTY); 

    /* for testing on NT only
    port2.WriteEx(sBuf, static_cast<DWORD>(strlen(sBuf)));
    SleepEx(INFINITE, TRUE);
    port2.ReadEx(pBuf, 10);
    SleepEx(INFINITE, TRUE);
    */

  }
  catch (CSerialException* pEx)
  {
    TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage().operator LPCTSTR());
    pEx->Delete();
  }

  delete [] pBuf;

  return FALSE;
}
