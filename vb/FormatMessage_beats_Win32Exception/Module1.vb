' http://pinvoke.net/default.aspx/kernel32.FormatMessage
' we want a valid win32 message string for this smartcard error...in a vb.net
' app: 2148532236

Imports System.Runtime.InteropServices
Imports System.Text

Namespace FormatMessage_beats_Win32Exception

    Friend Class Program
        Private Const FORMAT_MESSAGE_IGNORE_INSERTS As UInteger = &H200
        Private Const FORMAT_MESSAGE_FROM_SYSTEM As UInteger = &H1000

        <DllImport("kernel32.dll")> _
        Private Shared Function FormatMessage(dwFlags As UInteger, lpSource As IntPtr, dwMessageId As UInteger, dwLanguageId As UInteger, <Out> lpBuffer As StringBuilder, nSize As UInteger, _
            Arguments As IntPtr) As UInteger
        End Function

        Public Shared Sub Main(args As String())
            Dim sb = New StringBuilder(1024)
            ' access denied
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM Or FORMAT_MESSAGE_IGNORE_INSERTS, IntPtr.Zero, 5, 0, sb, 1024, _
                IntPtr.Zero)
            Dim win32errorString = sb.ToString()
            Console.WriteLine(sb.ToString())

            sb = New StringBuilder(1024)
            ' file not found
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM Or FORMAT_MESSAGE_IGNORE_INSERTS, IntPtr.Zero, 2, 0, sb, 1024, _
                IntPtr.Zero)
            win32errorString = sb.ToString()
            Console.WriteLine(sb.ToString())

            sb = New StringBuilder(1024)
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM Or FORMAT_MESSAGE_IGNORE_INSERTS, IntPtr.Zero, 2148532236, 0, sb, 1024, _
                IntPtr.Zero)
            win32errorString = sb.ToString()
            Console.WriteLine(sb.ToString())
        End Sub
    End Class
End Namespace