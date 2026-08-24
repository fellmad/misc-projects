package CInterface;

import com.sun.jna.Library;

public interface CInterface extends Library {
    public int printf(String format, String str);

    public int puts(String str);
}
