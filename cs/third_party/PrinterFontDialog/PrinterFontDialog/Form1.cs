using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace PrinterFontDialog
{
    public partial class Form1 : Form
    {
        private const string printerDriver = "winspool.drv";

        public Form1()
        {
            InitializeComponent();
        }

        private void ButtonClickHandler(object sender, EventArgs e)
        {
            switch ((sender as Button).Name)
            {
                case "btnNetFont":
                    using (FontDialog fontDialog = new FontDialog())
                    {
                        DialogResult dialogResult = fontDialog.ShowDialog();
                        if (dialogResult == DialogResult.OK)
                        {
                            lblExample.Text += "This is a example of .NET Font Dialog";
                            lblExample.Font = fontDialog.Font;
                        }
                    }
                    break;
                case "btnComFont":
                    LoadPrinterFontDialog();
                    break;
            }
        }

        private void LoadPrinterFontDialog()
        {
            bool success = false;
            UnSafeAPI.PRINTER_DEFAULTS printerDefault = new UnSafeAPI.PRINTER_DEFAULTS();
            printerDefault.DataType = null;
            printerDefault.DevMode = IntPtr.Zero;
            printerDefault.DesiredAccess = UnSafeAPI.PRINTER_ACCESS_USE;
            IntPtr hPrinter = IntPtr.Zero;
            int pcbNeeded = 0;
            string name = txtPrinterName.Text;
            Boolean blnResult = UnSafeAPI.OpenPrinter(name, out hPrinter, ref printerDefault);
            UnSafeAPI.GetPrinter(hPrinter, 2, IntPtr.Zero, 0, out pcbNeeded);
            UnSafeAPI.LOGFONT lf = new UnSafeAPI.LOGFONT();
            lf.lfFaceName = "Arial";

            //FontStyle.Italic
            lf.lfItalic = 1;
            //FontStyle.Regular
            lf.lfWeight = 400;
            //FontStyle.Bold
            lf.lfWeight = 700;
            //FontStyle.Strikeout
            lf.lfStrikeOut = 1;
            //FontStyle.Underline
            lf.lfUnderline = 1;
            IntPtr lplf = Marshal.AllocHGlobal(Marshal.SizeOf(lf));
            Marshal.StructureToPtr(lf, lplf, false);
            IntPtr ptrPrinterInfo = Marshal.AllocHGlobal(pcbNeeded);
            int nJunk;
            UnSafeAPI.GetPrinter(hPrinter, 2, ptrPrinterInfo, pcbNeeded, out nJunk);
            UnSafeAPI.PRINTER_INFO_2 PrinterInfo_2 = (UnSafeAPI.PRINTER_INFO_2)Marshal.PtrToStructure(ptrPrinterInfo, typeof(UnSafeAPI.PRINTER_INFO_2));
            
            UnSafeAPI.DEVMODE PrinterDevMode_2 = (UnSafeAPI.DEVMODE)Marshal.PtrToStructure(PrinterInfo_2.pDevMode, typeof(UnSafeAPI.DEVMODE));

            //2 for landscape & 1 for portrait
            PrinterDevMode_2.dmOrientation = 2;

            //  Reverse the struct back into bytes and then set the printer with the new value
            Marshal.StructureToPtr(PrinterDevMode_2, PrinterInfo_2.pDevMode, true);
            Marshal.StructureToPtr(PrinterInfo_2, ptrPrinterInfo, true);
            blnResult = UnSafeAPI.SetPrinter(hPrinter, 2, ptrPrinterInfo, 0);
            IntPtr printerDC = UnSafeAPI.CreateDC(printerDriver, name, PrinterInfo_2.pPortName, IntPtr.Zero);
            UnSafeAPI.CHOOSEFONT cf = new UnSafeAPI.CHOOSEFONT();
            cf.lStructSize = Marshal.SizeOf(typeof(UnSafeAPI.CHOOSEFONT));
            cf.hwndOwner = this.Handle;
            cf.hDC = printerDC;
            cf.Flags = UnSafeAPI.CF_Both | UnSafeAPI.CF_EFFECTS;
            cf.lpLogFont = lplf.ToInt32();
            //cf.iPointSize = Convert.ToInt32(Ofont.FontSize) * 10;
            IntPtr lpcf = Marshal.AllocHGlobal(Marshal.SizeOf(cf));
            Marshal.StructureToPtr(cf, lpcf, false);
            if (UnSafeAPI.ChooseFont(lpcf))
            {
                UnSafeAPI.CHOOSEFONT newcf = (UnSafeAPI.CHOOSEFONT)Marshal.PtrToStructure(lpcf, typeof(UnSafeAPI.CHOOSEFONT));
                UnSafeAPI.LOGFONT newlf = (UnSafeAPI.LOGFONT)Marshal.PtrToStructure(new IntPtr(newcf.lpLogFont), typeof(UnSafeAPI.LOGFONT));
                success = true;
            }
            UnSafeAPI.DeleteDC(printerDC);
            Marshal.FreeHGlobal(lpcf);
            Marshal.FreeHGlobal(lplf);
        }
    }
}
