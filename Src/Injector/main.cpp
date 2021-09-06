#include "stdafx.h"

int main(void)
{
    /*TCHAR szCommand[] = TEXT("Victim.exe");
    TCHAR szHookerDll[] = TEXT("BehaviorBasedEngine.dll");

    STARTUPINFO si = { sizeof(STARTUPINFO), };
    PROCESS_INFORMATION pi = { 0, };
    BOOL bRet = DetourCreateProcessWithDll(NULL, szCommand, NULL,
        NULL, TRUE, CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED, NULL, NULL,
        &si, &pi, "BehaviorBasedEngine.dll", NULL);

    ResumeThread(pi.hThread);
    WaitForSingleObject(pi.hProcess, 5000);*/

    std::tstring strDir = core::GetCurrentDirectoryW();
    std::tstring strLogFile = strDir + TEXT("/behavior.log");

    HANDLE hFile = core::CreateFile(strLogFile.c_str(), core::GENERIC_READ_, core::OPEN_EXISTING_, 0);
    wchar_t buf[51];
    DWORD dwRead;
    if (NULL != hFile)
    {
        bool result = core::ReadFile(hFile, buf, 50, &dwRead);
        if (result) {
            tprintf(TEXT("%d\n"), dwRead);
            tprintf(TEXT("%s\n"), buf);
            std::string strLogA = core::UTF8FromWCS(buf);
            tprintf(TEXT("%s\n"), strLogA.c_str());
        }
        else {
            tprintf(TEXT("실패하였습니다."));
        }
 /*       std::string strLogA = core::UTF8FromWCS(strLog);
        core::WriteFile(hFile, strLogA.c_str(), strLogA.length(), &dwWrittenSize);
        core::CloseFile(hFile);*/
    }

    //std::tstring strContents;
    //core::ReadFileContents(strLogFile, strContents);
    //tprintf(TEXT("%s\n"), strContents.c_str());
    return 0;
}