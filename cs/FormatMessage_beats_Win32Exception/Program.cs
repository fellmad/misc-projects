// http://pinvoke.net/default.aspx/kernel32.FormatMessage
// we want a valid win32 message string for this smartcard error...in a vb.net
// app: 2148532236

using System;
using System.Runtime.InteropServices;
using System.Text;

namespace FormatMessage_beats_Win32Exception {

    internal class Program {
        private const uint FORMAT_MESSAGE_IGNORE_INSERTS = 0x00000200;
        private const uint FORMAT_MESSAGE_FROM_SYSTEM = 0x00001000;

        [DllImport("kernel32.dll")]
        private static extern uint FormatMessage(
            uint dwFlags,
            IntPtr lpSource,
            uint dwMessageId,
            uint dwLanguageId,
            [Out] StringBuilder lpBuffer,
            uint nSize,
            IntPtr Arguments);

        private static void Main(string[] args) {
            var sb = new StringBuilder(1024);
            FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                IntPtr.Zero,
                5, // access denied
                0,
                sb,
                1024,
                IntPtr.Zero);
            var win32errorString = sb.ToString();
            Console.WriteLine(sb.ToString());

            sb = new StringBuilder(1024);
            FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                IntPtr.Zero,
                2, // file not found
                0,
                sb,
                1024,
                IntPtr.Zero);
            win32errorString = sb.ToString();
            Console.WriteLine(sb.ToString());

            sb = new StringBuilder(1024);
            FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                IntPtr.Zero,
                2148532236,
                0,
                sb,
                1024,
                IntPtr.Zero);
            win32errorString = sb.ToString();
            Console.WriteLine(sb.ToString());
        }
    }
}