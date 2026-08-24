setlocal
set classpath=.;c:\bitbucket\projects\java\jna\lib\*
pushd classes
java^
 -verbose^
 com/sun/jna/examples/HelloWorld parm1 a b c

popd
endlocal