
public class GetSystemTime {
    public static void main(String[] args) {
        Kernel32 lib = Kernel32.INSTANCE;
        Kernel32.SYSTEMTIME time = new Kernel32.SYSTEMTIME();
        lib.GetSystemTime(time);
        System.out.println("Today's integer value is " + time.wDay);
    }
}
