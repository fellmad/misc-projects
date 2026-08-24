package call_tlbimp;

import com.sun.jna.Native;
import com.sun.jna.Platform;
import com.sun.jna.platform.win32.COM.tlb.TlbImp;

public class Call_tlbimp {

    public static void main(String[] args) {
        System.out.println("Platform.C_LIBRARY_NAME: " + Platform.C_LIBRARY_NAME);
        System.out.println("Platform.WINDOWS: " + Platform.WINDOWS);
        System.out.println("Platform.ARCH: " + Platform.ARCH);
        System.out.println("Platform.is64Bit(): " + Platform.is64Bit());
        System.out.println("Platform.HAS_AWT: " + Platform.HAS_AWT);
        System.out.println("Platform.HAS_BUFFERS: " + Platform.HAS_BUFFERS);
        System.out.println("Platform.HAS_DLL_CALLBACKS: " + Platform.HAS_DLL_CALLBACKS);

        System.out.println("Native.DEFAULT_ENCODING: " + Native.DEFAULT_ENCODING);
        System.out.println("Native.VERSION: " + Native.VERSION);
        System.out.println("Native.VERSION_NATIVE: " + Native.VERSION_NATIVE);
        System.out.println("Native.LONG_SIZE: " + Native.LONG_SIZE);
        System.out.println("Native.POINTER_SIZE: " + Native.POINTER_SIZE);
        System.out.println("Native.SIZE_T_SIZE: " + Native.SIZE_T_SIZE);
        System.out.println("Native.WCHAR_SIZE: " + Native.WCHAR_SIZE);

        // run with cmd-line args: -tlb.file c:\temp_jna\BidiDisp.tlb      
        TlbImp tlbimp = new TlbImp(args);
    }
}
/*
output:
Platform.C_LIBRARY_NAME: msvcrt
Platform.WINDOWS: 2
Platform.ARCH: x86
Platform.is64Bit(): false
Platform.HAS_AWT: true
Platform.HAS_BUFFERS: true
Platform.HAS_DLL_CALLBACKS: true
Native.DEFAULT_ENCODING: utf8
Native.VERSION: 4.1.0
Native.VERSION_NATIVE: 4.0.0
Native.LONG_SIZE: 4
Native.POINTER_SIZE: 4
Native.SIZE_T_SIZE: 4
Native.WCHAR_SIZE: 2
Output directory sucessfully created.
INFO 2015-02-09 12:23:18.234 : Type of kind 'CoClass' found: BidiRequest
INFO 2015-02-09 12:23:18.327 : Type of kind 'Interface' found: IBidiRequest
INFO 2015-02-09 12:23:18.327 : Type of kind 'CoClass' found: BidiRequestContainer
INFO 2015-02-09 12:23:18.343 : Type of kind 'Interface' found: IBidiRequestContainer
INFO 2015-02-09 12:23:18.343 : Type of kind 'Interface' found: IEnumUnknown
INFO 2015-02-09 12:23:18.359 : Type of kind 'CoClass' found: BidiSpl
INFO 2015-02-09 12:23:18.374 : Type of kind 'Interface' found: IBidiSpl
7 files sucessfully written to: c:\temp\_jnaCOM_1423506198202\myPackage\ibidispllib
*/
