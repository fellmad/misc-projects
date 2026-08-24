from the cmd line:

where javac
C:\Program Files (x86)\Java\jdk1.8.0\bin\javac.exe

where java
C:\Program Files (x86)\Java\jdk1.8.0\bin\java.exe
C:\Windows\System32\java.exe
C:\ProgramData\Oracle\Java\javapath\java.exe

set classpath=.;c:\bitbucket\projects\java\jna\lib\*;%classpath%

c:\bitbucket\projects\java\jna\jnademo\CInterface>javac *java
Directory of c:\bitbucket\projects\java\jna\jnademo\CInterface
02/03/2015  01:41 PM               237 CInterface.class
01/28/2015  01:29 PM               181 CInterface.java
02/03/2015  01:41 PM             1,025 hello.class
01/28/2015  01:28 PM               800 hello.java

// go up one folder...
c:\bitbucket\projects\java\jna\jnademo>java CInterface.hello
You can enter you own text between quotes...
Syntax: java -jar /jna/dist/demo.jar "myowntext"
Hello World!

c:\bitbucket\projects\java\jna\jnademo>java CInterface.hello zzzzzzzzzzzzzzzzzzzz
zzzzzzzzzzzzzzzzzzzz
