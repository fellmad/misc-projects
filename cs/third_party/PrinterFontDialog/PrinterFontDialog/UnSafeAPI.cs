using System;
using System.Runtime.InteropServices;

namespace PrinterFontDialog
{
    public class UnSafeAPI
    {
        #region Constants

        /// <summary>
        /// To perform basic printing operations.
        /// </summary>
        public const int PRINTER_ACCESS_USE = 0x8;
        /// <summary>
        /// Size Constant defined for LogFont lfFaceName.
        /// </summary>
        public const int LF_FACESIZE = 32;
        /// <summary>
        /// Causes the dialog box to list only the screen fonts supported by the system. 
        /// </summary>
        public const int CF_SCREENFONTS = 0x00000001;
        /// <summary>
        /// Causes the dialog box to list only the fonts supported by the printer associated with the device context or information 
        /// context identified by the hDC member. It also causes the font type description label to appear at the bottom of the 
        /// Font dialog box. 
        /// Note: Windows 7 and later: The ChooseFont function ignores this flag for font enumeration.
        /// </summary>
        public const int CF_PRINTERFONTS = 0x00000002;
        /// <summary>
        /// Causes the dialog box to display the controls that allow the user to specify strikeout, underline, 
        /// and text color options. If this flag is set, you can use the rgbColors member to specify the initial text color. 
        /// You can use the lfStrikeOut and lfUnderline members of the structure pointed to by lpLogFont to specify the initial 
        /// settings of the strikeout and underline check boxes. ChooseFont can use these members to return the user's selections. 
        /// </summary>
        public const int CF_EFFECTS = 0x00000100;
        /// <summary>
        /// Causes the dialog box to list the available printer and screen fonts. The hDC member is a handle to the device context 
        /// or information context associated with the printer. This flag is a combination of the CF_SCREENFONTS and CF_PRINTERFONTS flags.
        /// Note: Windows 7 and later: The ChooseFont function ignores this flag for font enumeration. 
        /// </summary>
        public const int CF_Both = 0x00000003;
        /// <summary>
        /// Specifies that ChooseFont should use the structure pointed to by the lpLogFont member to initialize the dialog box controls. 
        /// </summary>
        public const int CF_INITTOLOGFONTSTRUCT = 0x00000040;

        #endregion
        
        /// <summary>
        /// The PRINTER_DEFAULTS structure specifies the default data type, environment, initialization data, and access rights for a printer. 
        /// </summary>
        public struct PRINTER_DEFAULTS
        {
            /// <summary>
            /// Pointer to a null-terminated string that specifies the default data type for a printer.
            /// </summary>
            public string DataType;
            /// <summary>
            /// Pointer to a DEVMODE structure that identifies the default environment and initialization data for a printer. 
            /// </summary>
            public IntPtr DevMode;
            /// <summary>
            /// Specifies desired access rights for a printer. 
            /// </summary>
            public uint DesiredAccess;
        }

        /// <summary>
        /// Defines the attributes of a font.
        /// </summary>
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct LOGFONT
        {
            /// <summary>
            /// Specifies the height, in logical units, of the font's character cell or character. The character height value 
            /// (also known as the em height) is the character cell height value minus the internal-leading value.
            /// </summary>
            public int lfHeight;
            /// <summary>
            /// Specifies the average width, in logical units, of characters in the font. If lfWidth is not zero, the aspect 
            /// ratio of the device is matched against the digitization aspect ratio of the available fonts to find the closest 
            /// match, determined by the absolute value of the difference. 
            /// </summary>
            public int lfWidth;
            /// <summary>
            /// Specifies the angle, in tenths of degrees, between the escapement vector and the x-axis of the device. 
            /// The escapement vector is parallel to the base line of a row of text.
            ///The lfEscapement member specifies both the escapement and orientation. 
            ///You should set lfEscapement and lfOrientation to the same value. 
            /// </summary>
            public int lfEscapement;
            /// <summary>
            /// Specifies the angle, in tenths of degrees, between each character's base line and the x-axis of the device.
            /// </summary>
            public int lfOrientation;
            /// <summary>
            /// Specifies the weight of the font in the range 0 through 1000. For example, 400 is normal and 700 is bold. 
            /// If this value is zero, a default weight is used.
            /// </summary>
            public int lfWeight;
            /// <summary>
            /// TRUE to specify an italic font.
            /// </summary>
            public byte lfItalic;
            /// <summary>
            /// TRUE to specify an underlined font.
            /// </summary>
            public byte lfUnderline;
            /// <summary>
            /// TRUE to specify a strikeout font.
            /// </summary>
            public byte lfStrikeOut;
            /// <summary>
            /// DEFAULT_CHARSET is set to a value based on the current system locale. For example, when the system locale is English (United States), the value is ANSI_CHARSET.
            /// This member is important in the font mapping process. To ensure consistent results, specify a specific character 
            /// set. If you specify a typeface name in the lfFaceName member, make sure that the lfCharSet value matches the 
            /// character set of the typeface specified in lfFaceName. 
            /// </summary>
            public byte lfCharSet;
            /// <summary>
            /// Specifies the output precision. The output precision defines how closely the output must match the requested 
            /// font's height, width, character orientation, escapement, pitch, and font type. 
            /// </summary>
            public byte lfOutPrecision;
            /// <summary>
            /// Specifies the clipping precision. The clipping precision defines how to clip characters that are partially 
            /// outside the clipping region.
            /// </summary>
            public byte lfClipPrecision;
            /// <summary>
            /// Specifies the output quality. The output quality defines how carefully the Windows Graphics Device Interface 
            /// (GDI) must attempt to match the logical-font attributes to those of an actual physical font.
            /// </summary>
            public byte lfQuality;
            /// <summary>
            /// Specifies the pitch and family of the font
            /// </summary>
            public byte lfPitchAndFamily;
            /// <summary>
            /// Specifies a null-terminated string that specifies the typeface name of the font. 
            /// The length of this string must not exceed 32 characters, including the terminating null character.
            /// The EnumFontFamilies function can be used to enumerate the typeface names of all currently available fonts.
            /// </summary>
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = LF_FACESIZE)]
            public string lfFaceName;
        }

        /// <summary>
        /// The PRINTER_INFO_2 structure specifies detailed printer information. 
        /// </summary>
        [StructLayout(LayoutKind.Sequential)]
        public struct PRINTER_INFO_2
        {
            /// <summary>
            /// A pointer to a null-terminated string identifying the server that controls the printer. If this string is NULL, the printer is controlled locally.
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pServerName;
            /// <summary>
            /// A pointer to a null-terminated string that specifies the name of the printer.
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pPrinterName;
            /// <summary>
            /// A pointer to a null-terminated string that identifies the sharepoint for the printer. (This string is used only if the PRINTER_ATTRIBUTE_SHARED constant was set for the Attributes member.) 
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pShareName;
            /// <summary>
            /// A pointer to a null-terminated string that identifies the port(s) used to transmit data to the printer.
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pPortName;
            /// <summary>
            /// A pointer to a null-terminated string that specifies the name of the printer driver.
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pDriverName;
            /// <summary>
            /// A pointer to a null-terminated string that provides a brief description of the printer.
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pComment;
            /// <summary>
            /// A pointer to a null-terminated string that specifies the physical location of the printer.
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pLocation;
            /// <summary>
            /// A pointer to a DEVMODE structure that defines default printer data such as the paper orientation and the resolution. 
            /// </summary>
            public IntPtr pDevMode;
            /// <summary>
            /// A pointer to a null-terminated string that specifies the name of the file used to create the separator page. This page is used to separate print jobs sent to the printer.
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pSepFile;
            /// <summary>
            /// A pointer to a null-terminated string that specifies the name of the print processor used by the printer. You can use the EnumPrintProcessors function to obtain a list of print processors installed on a server. 
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pPrintProcessor;
            /// <summary>
            /// A pointer to a null-terminated string that specifies the data type used to record the print job. You can use the EnumPrintProcessorDatatypes function to obtain a list of data types supported by a specific print processor. 
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pDatatype;
            /// <summary>
            /// A pointer to a null-terminated string that specifies the default print-processor parameters.
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string pParameters;
            /// <summary>
            /// A pointer to a SECURITY_DESCRIPTOR structure for the printer. This member may be NULL. 
            /// </summary>
            public IntPtr pSecurityDescriptor;
            public Int32 Attributes;
            /// <summary>
            /// A priority value that the spooler uses to route print jobs.
            /// </summary>
            public Int32 Priority;
            /// <summary>
            /// The default priority value assigned to each print job.
            /// </summary>
            public Int32 DefaultPriority;
            /// <summary>
            /// The earliest time at which the printer will print a job. 
            /// </summary>
            public Int32 StartTime;
            /// <summary>
            /// The latest time at which the printer will print a job. 
            /// </summary>
            public Int32 UntilTime;
            /// <summary>
            /// 
            /// </summary>
            public Int32 Status;
            /// <summary>
            /// The number of print jobs that have been queued for the printer.
            /// </summary>
            public Int32 cJobs;
            /// <summary>
            /// The average number of pages per minute that have been printed on the printer.
            /// </summary>
            public Int32 AveragePPM;
        }

        /// <summary>
        /// The DEVMODE data structure contains information about the initialization and environment of a printer or a display device. 
        /// </summary>
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct DEVMODE
        {
            /// <summary>
            /// Name of the printer.
            /// </summary>
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = LF_FACESIZE)]
            public string dmDeviceName;
            public short dmSpecVersion;
            /// <summary>
            /// Driver version Number
            /// </summary>
            public short dmDriverVersion;
            /// <summary>
            /// Specifies the size, in bytes, of the DEVMODE structure, not including any private driver-specific data that 
            /// might follow the structure's public members. Set this member to sizeof (DEVMODE) to indicate the version of 
            /// the DEVMODE structure being used. 
            /// </summary>
            public short dmSize;
            /// <summary>
            /// Contains the number of bytes of private driver-data that follow this structure. If a device driver does not use 
            /// device-specific information, set this member to zero.
            /// </summary>
            public short dmDriverExtra;
            /// <summary>
            /// Specifies whether certain members of the DEVMODE structure have been initialized. If a member is initialized, 
            /// its corresponding bit is set, otherwise the bit is clear. A driver supports only those DEVMODE members that are 
            /// appropriate for the printer or display technology. 
            /// </summary>
            public int dmFields;
            /// <summary>
            /// For printer devices only, selects the orientation of the paper. This member can be either 
            /// DMORIENT_PORTRAIT (1) or DMORIENT_LANDSCAPE (2).
            /// </summary>
            public short dmOrientation;
            /// <summary>
            /// For printer devices only, selects the size of the paper to print on. This member can be set to zero if the 
            /// length and width of the paper are both set by the dmPaperLength and dmPaperWidth members. Otherwise, 
            /// the dmPaperSize member can be set to a device specific value greater than or equal to DMPAPER_USER or 
            /// to one of the following predefined values. 
            /// </summary>
            public short dmPaperSize;
            /// <summary>
            /// For printer devices only, overrides the length of the paper specified by the dmPaperSize member, 
            /// either for custom paper sizes or for devices such as dot-matrix printers that can print on a page of 
            /// arbitrary length. These values, along with all other values in this structure that specify a physical length, 
            /// are in tenths of a millimeter. 
            /// </summary>
            public short dmPaperLength;
            /// <summary>
            /// For printer devices only, overrides the width of the paper specified by the dmPaperSize member. 
            /// </summary>
            public short dmPaperWidth;
            /// <summary>
            /// Specifies the factor by which the printed output is to be scaled. The apparent page size is scaled from the 
            /// physical page size by a factor of dmScale /100. For example, a letter-sized page with a dmScale value of 50 
            /// would contain as much data as a page of 17- by 22-inches because the output text and graphics would be half 
            /// their original height and width. 
            /// </summary>
            public short dmScale;
            /// <summary>
            /// Selects the number of copies printed if the device supports multiple-page copies.
            /// </summary>
            public short dmCopies;
            /// <summary>
            /// Specifies the paper source. To retrieve a list of the available paper sources for a printer, 
            /// use the DeviceCapabilities function with the DC_BINS flag. 
            /// </summary>
            public short dmDefaultSource;
            /// <summary>
            /// Specifies the printer resolution. There are four predefined device-independent values:
            /// DMRES_HIGH,DMRES_MEDIUM,DMRES_LOW,DMRES_DRAFT.
            /// If a positive value is specified, it specifies the number of dots per inch (DPI) and is therefore device dependent.
            /// </summary>
            public short dmPrintQuality;
            /// <summary>
            /// Switches between color and monochrome on color printers. The following are the possible values:
            /// DMCOLOR_COLOR,DMCOLOR_MONOCHROME
            /// </summary>
            public short dmColor;
            /// <summary>
            /// Selects duplex or double-sided printing for printers capable of duplex printing.
            /// DMDUP_SIMPLEX,DMDUP_HORIZONTAL,DMDUP_VERTICAL
            /// </summary>
            public short dmDuplex;
            /// <summary>
            /// Specifies the y-resolution, in dots per inch, of the printer. If the printer initializes this member, 
            /// the dmPrintQuality member specifies the x-resolution, in dots per inch, of the printer.
            /// </summary>
            public short dmYResolution;
            /// <summary>
            /// Specifies how TrueType fonts should be printed. This member can be one of the following values:
            /// DMTT_BITMAP,DMTT_DOWNLOAD,DMTT_DOWNLOAD_OUTLINE,DMTT_SUBDEV
            /// </summary>
            public short dmTTOption;
            /// <summary>
            /// Specifies whether collation should be used when printing multiple copies. (This member is ignored unless the 
            /// printer driver indicates support for collation by setting the dmFields member to DM_COLLATE.) 
            /// This member can be one of the following values: 
            /// DMCOLLATE_TRUE,DMCOLLATE_FALSE
            /// </summary>
            public short dmCollate;
            /// <summary>
            /// A zero-terminated character array that specifies the name of the form to use; for example, "Letter" or "Legal". 
            /// A complete set of names can be retrieved by using the EnumForms function. 
            /// </summary>
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = LF_FACESIZE)]
            public string dmFormName;
            public short dmUnusedPadding;
            /// <summary>
            /// Specifies the color resolution, in bits per pixel, of the display device (for example: 4 bits for 16 colors, 
            /// 8 bits for 256 colors, or 16 bits for 65,536 colors). Display drivers use this member, for example, 
            /// in the ChangeDisplaySettings function. Printer drivers do not use this member. 
            /// </summary>
            public int dmBitsPerPel;
            /// <summary>
            /// Specifies the width, in pixels, of the visible device surface. Display drivers use this member, for example, 
            /// in the ChangeDisplaySettings function. Printer drivers do not use this member. 
            /// </summary>
            public int dmPelsWidth;
            /// <summary>
            /// Specifies the height, in pixels, of the visible device surface. Display drivers use this member, for example, 
            /// in the ChangeDisplaySettings function. Printer drivers do not use this member. 
            /// </summary>
            public int dmPelsHeight;
            /// <summary>
            /// Specifies the device's display mode. This member can be a combination of the following values:
            /// DM_GRAYSCALE, DM_INTERLACED
            /// </summary>
            public int dmDisplayFlags;
            /// <summary>
            /// Specifies the frequency, in hertz (cycles per second), of the display device in a particular mode. 
            /// This value is also known as the display device's vertical refresh rate. 
            /// </summary>
            public int dmDisplayFrequency;
        }

        /// <summary>
        /// The CHOOSEFONT structure contains information that the ChooseFont function uses to initialize the Font dialog box. After the user closes the dialog box, the system returns information about the user's selection in this structure. 
        /// </summary>
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct CHOOSEFONT
        {
            /// <summary>
            /// Specifies the length of the structure, in bytes. 
            /// </summary>
            public int lStructSize;
            /// <summary>
            /// Handle to the window that owns the dialog box. This member can be any valid window handle, or it can be NULL if the dialog box has no owner. 
            /// </summary>
            public IntPtr hwndOwner;
            /// <summary>
            /// Handle to the device context or information context of the printer whose fonts will be listed in the dialog box. 
            /// This member is used only if the Flags member specifies the CF_PRINTERFONTS or CF_BOTH flag; otherwise, 
            /// this member is ignored. 
            /// </summary>
            public IntPtr hDC;
            /// <summary>
            /// Pointer to a structure. If you set the CF_INITTOLOGFONTSTRUCT flag in the Flags member and initialize the LOGFONT  members, 
            /// the ChooseFont function initializes the dialog box with a font that matches the LOGFONT members. 
            /// If the user clicks the OK button, ChooseFont sets the members of the LOGFONT structure based on the user's selections. 
            /// </summary>
            public int lpLogFont;
            /// <summary>
            /// Specifies the size of the selected font, in units of 1/10 of a point. 
            /// The ChooseFont function sets this value after the user closes the dialog box. 
            /// </summary>
            public int iPointSize;
            /// <summary>
            /// A set of bit flags that you can use to initialize the Font dialog box. When the dialog box returns, 
            /// it sets these flags to indicate the user input.
            /// </summary>
            public int Flags;
            /// <summary>
            /// If the CF_EFFECTS flag is set, rgbColors specifies the initial text color. When ChooseFont returns successfully, 
            /// this member contains the RGB value of the text color that the user selected. To create a COLORREF color value, 
            /// use the RGB macro. 
            /// </summary>
            public int rgbColors;
            /// <summary>
            /// Specifies application-defined data that the system passes to the hook procedure identified by the lpfnHook member. 
            /// When the system sends the WM_INITDIALOG message to the hook procedure, the message's lParam parameter is a pointer 
            /// to the CHOOSEFONT structure specified when the dialog was created. The hook procedure can use this pointer to get 
            /// the lCustData value.
            /// </summary>
            public int lCustData;
            /// <summary>
            /// Pointer to a CFHookProc hook procedure that can process messages intended for the dialog box. 
            /// This member is ignored unless the CF_ENABLEHOOK flag is set in the Flags member. 
            /// </summary>
            public int lpfnHook;
            /// <summary>
            /// Pointer to a null-terminated string that names the dialog box template resource in the module identified by the 
            /// hInstance member. This template is substituted for the standard dialog box template. For numbered dialog box 
            /// resources, lpTemplateName can be a value returned by the MAKEINTRESOURCE macro. This member is ignored unless 
            /// the CF_ENABLETEMPLATE flag is set in the Flags member. 
            /// </summary>
            public int lpTemplateName;
            /// <summary>
            /// If the CF_ENABLETEMPLATEHANDLE flag is set in the Flags member, hInstance is a handle to a memory object 
            /// containing a dialog box template. If the CF_ENABLETEMPLATE flag is set, hInstance is a handle to a module 
            /// that contains a dialog box template named by the lpTemplateName member. If neither CF_ENABLETEMPLATEHANDLE 
            /// nor CF_ENABLETEMPLATE is set, this member is ignored. 
            /// </summary>
            public int hInstance;
            /// <summary>
            /// Pointer to a buffer that contains style data. If the CF_USESTYLE flag is specified, ChooseFont uses the data in 
            /// this buffer to initialize the Font Style combo box. When the user closes the dialog box, ChooseFont copies the 
            /// string in the Font Style combo box into this buffer. 
            /// </summary>
            public int lpszStyle;
            /// <summary>
            /// Specifies the type of the selected font when ChooseFont returns.
            /// </summary>
            public short nFontType;
            /// <summary>
            /// Specifies the minimum point size a user can select. ChooseFont recognizes this member only if the CF_LIMITSIZE 
            /// flag is specified. 
            /// </summary>
            public int nSizeMin;
            /// <summary>
            /// Specifies the maximum point size a user can select. ChooseFont recognizes this member only if the CF_LIMITSIZE 
            /// flag is specified. 
            /// </summary>
            public int nSizeMax;
        }

        /// <summary>
        /// The OpenPrinter function retrieves a handle to the specified printer or print server or other types of handles 
        /// in the print subsystem. 
        /// </summary>
        /// <param name="szPrinter">A pointer to a null-terminated string that specifies the name of the printer or print server.</param>
        /// <param name="hPrinter">A pointer to a variable that receives a handle (not thread safe) to the open printer or print server object.</param>
        /// <param name="pd">A pointer to a PRINTER_DEFAULTS structure. This value can be NULL.</param>
        /// <returns></returns>
        [DllImport("winspool.Drv", EntryPoint = "OpenPrinterA", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.StdCall)]
        public static extern bool OpenPrinter([MarshalAs(UnmanagedType.LPStr)]string szPrinter, out IntPtr hPrinter, ref PRINTER_DEFAULTS pd);

        /// <summary>
        /// The GetPrinter function retrieves information about a specified printer. 
        /// </summary>
        /// <param name="hPrinter">A handle to the printer for which the function retrieves information. Use the OpenPrinter or AddPrinter function to retrieve a printer handle. </param>
        /// <param name="dwLevel">The level or type of structure that the function stores into the buffer pointed to by pPrinter. This value can be 1, 2, 3, 4, 5, 6, 7, 8 or 9.</param>
        /// <param name="pPrinter">A pointer to a buffer that receives a structure containing information about the specified printer. The buffer must be large enough to receive the structure and any strings or other data to which the structure members point. If the buffer is too small, the pcbNeeded parameter returns the required buffer size. </param>
        /// <param name="cbBuf">The size, in bytes, of the buffer pointed to by pPrinter. </param>
        /// <param name="pcbNeeded">A pointer to a variable that the function sets to the size, in bytes, of the printer information. If cbBuf is smaller than this value, GetPrinter fails, and the value represents the required buffer size. If cbBuf is equal to or greater than this value, GetPrinter succeeds, and the value represents the number of bytes stored in the buffer.</param>
        /// <returns>If the function succeeds, the return value is a nonzero value. If the function fails, the return value is zero.</returns>
        [DllImport("winspool.drv", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern bool GetPrinter(IntPtr hPrinter, int dwLevel, IntPtr pPrinter, int cbBuf, out int pcbNeeded);

        /// <summary>
        /// The SetPrinter function sets the data for a specified printer or sets the state of the specified printer by pausing printing, resuming printing, or clearing all print jobs. 
        /// </summary>
        /// <param name="hPrinter">A handle to the printer. Use the OpenPrinter, OpenPrinter2, or AddPrinter function to retrieve a printer handle. </param>
        /// <param name="Level">The type of data that the function stores into the buffer pointed to by pPrinter. If the Command parameter is not equal to zero, the Level parameter must be zero. This value can be 0, 2, 3, 4, 5, 6, 7, 8, or 9.</param>
        /// <param name="pPrinter">A pointer to a buffer containing data to set for the printer, or containing information for the command specified by the Command parameter. The type of data in the buffer is determined by the value of Level.</param>
        /// <param name="Command">The action performed by the SetPrinter function. If the Level parameter is nonzero, Command must be zero. 
        /// In this case, the printer retains its current state and the function reconfigures the printer data as specified by 
        /// the Level and pPrinter parameters. If the Level parameter is zero, 
        /// Command can be one of the following values to set the state of the printer (PRINTER_CONTROL_PAUSE, PRINTER_CONTROL_PURGE, PRINTER_CONTROL_RESUME, PRINTER_CONTROL_SET_STATUS).</param>
        /// <returns>If the function succeeds, the return value is a nonzero value. If the function fails, the return value is zero. 
        /// If Level is 7 and the publish action failed, SetPrinter returns ERROR_IO_PENDING and attempts to complete the 
        /// action in the background. If Level is 7 and the update action failed, SetPrinter returns ERROR_FILE_NOT_FOUND.
        /// </returns>
        [DllImport("winspool.drv", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern bool SetPrinter(IntPtr hPrinter, int Level, IntPtr pPrinter, uint Command);

        /// <summary>
        /// The CreateDC function creates a device context (DC) for a device using the specified name. 
        /// </summary>
        /// <param name="lpszDriver">A pointer to a null-terminated character string that specifies either DISPLAY or the name of a specific display device or the name of a print provider, which is usually WINSPOOL.</param>
        /// <param name="lpszDevice">A pointer to a null-terminated character string that specifies the name of the specific output device being used. To obtain valid names for displays, call EnumDisplayDevices. 
        /// If lpszDriver is DISPLAY or the device name of a specific display device, then lpszDevice must be NULL or that same device name. If lpszDevice is NULL, then a DC is created for the primary display device. 
        /// If there are multiple monitors on the system, calling CreateDC(TEXT("DISPLAY"),NULL,NULL,NULL) will create a DC covering all the monitors. </param>
        /// <param name="lpszOutput">This parameter is ignored and should be set to NULL. It is provided only for compatibility with 16-bit Windows.</param>
        /// <param name="lpInitData">A pointer to a DEVMODE structure containing device-specific initialization data for the device driver. The DocumentProperties function retrieves this structure filled in for a specified device. The lpInitData parameter must be NULL if the device driver is to use the default initialization (if any) specified by the user. 
        /// If lpszDriver is DISPLAY, then lpInitData must be NULL. The display device's current DEVMODE is used.</param>
        /// <returns>If the function succeeds, the return value is the handle to a DC for the specified device. 
        /// If the function fails, the return value is NULL. 
        /// The function will return NULL for a DEVMODE structure other than the current DEVMODE.</returns>
        [DllImport("gdi32.dll")]
        public static extern IntPtr CreateDC(string lpszDriver, string lpszDevice, string lpszOutput, IntPtr lpInitData);

        /// <summary>
        /// Creates a Font dialog box that enables the user to choose attributes for a logical font. These attributes include a font family and associated font style, a point size, effects (underline, strikeout, and text color), and a script (or character set).
        /// </summary>
        /// <param name="lpcf">Pointer to a CHOOSEFONT structure that contains information used to initialize the dialog box. When ChooseFont returns, this structure contains information about the user's font selection. </param>
        /// <returns>If the user clicks the OK button of the dialog box, the return value is TRUE. 
        /// The members of the CHOOSEFONT structure indicate the user's selections. 
        /// If the user cancels or closes the Font dialog box or an error occurs, the return value is FALSE.</returns>
        [DllImport("comdlg32.dll", CharSet = CharSet.Auto, EntryPoint = "ChooseFont")]
        public extern static bool ChooseFont(IntPtr lpcf);

        /// <summary>
        /// The DeleteDC function deletes the specified device context (DC). 
        /// </summary>
        /// <param name="hdc">A handle to the device context.</param>
        /// <returns>If the function succeeds, the return value is nonzero. If the function fails, the return value is zero.</returns>
        [DllImport("gdi32.dll", SetLastError = true, CallingConvention = CallingConvention.StdCall)]
        public extern static int DeleteDC(IntPtr hdc);
    }
}
