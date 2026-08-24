using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

class Program {

    /// <summary>
    /// http://pinvoke.net/default.aspx/kernel32/WTSGetActiveConsoleSessionId.html
    /// The WTSGetActiveConsoleSessionId function retrieves the Remote Desktop
    /// Services session that is currently attached to the physical console. 
    /// The physical console is the monitor, keyboard, and mouse.
    /// Note that it is not necessary that Remote Desktop Services be running
    /// for this function to succeed.
    /// </summary>
    /// <returns>
    /// The session identifier of the session that is attached to the physical
    /// console. If there is no session attached to the physical console, (for
    /// example, if the physical console session is in the process
    /// of being attached or detached), this function returns 0xFFFFFFFF.
    /// </returns>
    [DllImport("kernel32.dll")]
    private static extern uint WTSGetActiveConsoleSessionId();

    /// <summary>
    /// http://pinvoke.net/default.aspx/wtsapi32/WTSSendMessage.html
    /// The WTSSendMessage function displays a message box on the client desktop
    /// of a specified Terminal Services session.
    /// </summary>
    [DllImport("wtsapi32.dll", SetLastError = true)]
    static extern bool WTSSendMessage(
        IntPtr hServer,
        [MarshalAs(UnmanagedType.I4)] int SessionId,
        String pTitle,
        [MarshalAs(UnmanagedType.U4)] int TitleLength,
        String pMessage,
        [MarshalAs(UnmanagedType.U4)] int MessageLength,
        [MarshalAs(UnmanagedType.U4)] int Style,
        [MarshalAs(UnmanagedType.U4)] int Timeout,
        [MarshalAs(UnmanagedType.U4)] out int pResponse,
        bool bWait);

    public static IntPtr WTS_CURRENT_SERVER_HANDLE = IntPtr.Zero;

    ///<summary>
    /// http://pinvoke.net/default.aspx/Enums.MessageBoxOptions
    /// Flags that define appearance and behaviour of a standard message box
    /// displayed by a call to the MessageBox function.
    /// </summary>    
    [Flags]
    public enum MessageBoxOpts : uint {
        OkOnly = 0x000000,
        OkCancel = 0x000001,
        AbortRetryIgnore = 0x000002,
        YesNoCancel = 0x000003,
        YesNo = 0x000004,
        RetryCancel = 0x000005,
        CancelTryContinue = 0x000006,
        IconHand = 0x000010,
        IconQuestion = 0x000020,
        IconExclamation = 0x000030,
        IconAsterisk = 0x000040,
        UserIcon = 0x000080,
        IconWarning = IconExclamation,
        IconError = IconHand,
        IconInformation = IconAsterisk,
        IconStop = IconHand,
        DefButton1 = 0x000000,
        DefButton2 = 0x000100,
        DefButton3 = 0x000200,
        DefButton4 = 0x000300,
        ApplicationModal = 0x000000,
        SystemModal = 0x001000,
        TaskModal = 0x002000,
        Help = 0x004000,
        NoFocus = 0x008000,
        SetForeground = 0x010000,
        DefaultDesktopOnly = 0x020000,
        Topmost = 0x040000,
        Right = 0x080000,
        RTLReading = 0x100000
    }

    public static void Main(string[] args) {
        var activeConsoleSessionId = WTSGetActiveConsoleSessionId();

        var title = "dialog 1: exclamation icon with yes/no buttons.";
        var content = "press a button";
        int dialogResponse = 0;
        var sendMsgResult = WTSSendMessage(
            WTS_CURRENT_SERVER_HANDLE,
            (int)activeConsoleSessionId,
            title,
            title.Length,
            content,
            content.Length,
            (int)MessageBoxIcon.Exclamation | (int)MessageBoxOpts.YesNo,
            0, // wait forever
            out dialogResponse,
            true);

        var dialogResult = (DialogResult)dialogResponse;
        var dialogResultString = dialogResult.ToString();

        title = "dialog 2: infomation icon with results:";
        content = string.Format("dialogResponse: {0} '{1}'{2}{2}sendMsgResult: {3}",
            dialogResponse,
            dialogResultString,
            Environment.NewLine,
            sendMsgResult);
        
        sendMsgResult = WTSSendMessage(
            WTS_CURRENT_SERVER_HANDLE,
            (int)activeConsoleSessionId,
            title,
            title.Length,
            content,
            content.Length,
            (int)MessageBoxIcon.Information | (int)MessageBoxOpts.OkOnly,
            0, // wait forever
            out dialogResponse,
            true);
    }
}
