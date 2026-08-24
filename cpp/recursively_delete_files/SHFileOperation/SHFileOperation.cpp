// https://msdn.microsoft.com/en-us/library/windows/desktop/bb762164(v=vs.85).aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb759795(v=vs.85).aspx

#include <iostream>
#include <string>
#include <atlstr.h>
#include <atlpath.h>
#include <shellapi.h>

int main()
{
    CStringW tempPath;
    int rc = ::GetTempPathW(MAX_PATH, tempPath.GetBuffer(MAX_PATH));
    tempPath.ReleaseBuffer();
    if (rc <= 0) {
        const auto lastError = ::GetLastError();
        std::wcout << L"GetTempPath(): " << lastError << std::endl;
    }

    CPathW testPath(tempPath);
    testPath.Append(LR"(a\b\c\d\e)");

    CStringW mkdirCmd = L"md ";
    mkdirCmd += testPath;
    rc = std::system(CW2A(mkdirCmd));
    if (0 != rc) {
        std::wcout << L"command failed: " << mkdirCmd.GetString() << std::endl;
    }
    else {
        std::wcout << L"command succeeded: " << mkdirCmd.GetString() << std::endl;
    }

    testPath.RemoveFileSpec();  // 'go up' one level
    testPath.RemoveFileSpec();  // another

    CStringW testPathString = testPath;
    testPathString.AppendChar(0);   // need trailing zero for SHFileOperationW()

    std::wcout << L"deleting: " << testPathString.GetString() << std::endl;

    SHFILEOPSTRUCTW op {};
    op.wFunc = FO_DELETE;
    op.pFrom = testPathString;
    op.fFlags |= FOF_NO_UI;
    rc = ::SHFileOperationW(&op);

    if (0 == rc) {
        std::wcout << L"SHFileOperationW() succeeded" << std::endl;
    }
    else {
        std::wcout << L"SHFileOperationW() fail: " << rc << std::endl;
    }
}