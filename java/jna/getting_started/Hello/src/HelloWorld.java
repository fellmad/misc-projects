// directory of c:\bitbucket\projects\java\jna\lib:
//  jna-4.1.0.jar
//  jna-platform-4.1.0.jar
// build:
//  set classpath=c:\bitbucket\projects\java\jna\lib\jna-4.1.0.jar;.
//      or
//  set classpath=.;../../lib/*
//
//  javac HelloWorld.java
//  java HelloWorld a b c
//      Hello, World
//      Argument 0: a
//      Argument 1: b
//      Argument 2: c
//
// notes: %classpath% does not seem to be case-sensitive;
//        make sure current folder '.' is in %classpath% for the java cmd.
//        forward slashes in %classpath% seem better...

package com.sun.jna.examples;
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Platform;

public class HelloWorld {

    // This is the standard, stable way of mapping, which supports extensive
    // customization and mapping of Java to native types.

    public interface CLibrary extends Library {
        CLibrary INSTANCE =
            (CLibrary) Native.loadLibrary((Platform.isWindows() ? "msvcrt" : "c"), CLibrary.class);
        void printf(String format, Object... args);
    }

    public static void main(String[] args) {
        CLibrary.INSTANCE.printf("Hello, World\n");
        for (int i = 0; i < args.length; i++) {
            CLibrary.INSTANCE.printf("Argument %d: %s\n", i, args[i]);
        }
    }
}