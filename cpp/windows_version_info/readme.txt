this is in the latest windows SDK stuff:
macro: IsWindowsVersionOrGreater(WORD
  wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor)

look at VersionHelpers.H

however, VersionHelpers.H is just a set of helper macros around the
VerifyVersionInfoW() call. VerifyVersionInfoW() is old. look in winbase.H; it
goes way back.