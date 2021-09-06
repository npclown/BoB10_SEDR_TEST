#include "pch.h"
#include "HookingFunc.h"

extern HINSTANCE g_hinstance;
static VOID(WINAPI* TrueSleep)(DWORD dwMilliseconds) = Sleep;
static VOID(WINAPI* TrueGetLocalTime)(LPSYSTEMTIME pSystemTime) = GetLocalTime;

void WriteBehaviorLog(std::tstring strLog)
{
    std::tstring strModuleFile = core::GetModuleFileName(g_hinstance);
    std::tstring strModuleDir = core::ExtractDirectory(strModuleFile);
    std::tstring strLogFile = strModuleDir + TEXT("/behavior.log");

    HANDLE hFile = core::CreateFile(strLogFile.c_str(), core::FILE_APPEND_DATA_, core::OPEN_ALWAYS_, 0);
    if (NULL != hFile)
    {
        DWORD dwWrittenSize = 0;
        std::string strLogA = core::UTF8FromWCS(strLog);
        core::WriteFile(hFile, strLogA.c_str(), strLogA.length(), &dwWrittenSize);
        core::CloseFile(hFile);
    }
}


VOID WINAPI Hooked_Sleep(DWORD dwMilliseconds)
{
    WriteBehaviorLog(core::Format(TEXT("Sleep(%d)\n"), dwMilliseconds));
    TrueSleep(dwMilliseconds);
}

VOID WINAPI Hooked_GetLocalTime(LPSYSTEMTIME pSystemTime)
{
    TrueGetLocalTime(pSystemTime);
    WriteBehaviorLog(core::Format(TEXT("GetLocalTime(%04d-%02d-%02d %02d:%02d:%02d)\n")
        , pSystemTime->wYear, pSystemTime->wMonth, pSystemTime->wDay
        , pSystemTime->wHour, pSystemTime->wMinute, pSystemTime->wSecond));
}

void InstallHookingFunc(void) {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)TrueSleep, Hooked_Sleep);
    DetourAttach(&(PVOID&)TrueGetLocalTime, Hooked_GetLocalTime);
    DetourTransactionCommit();
}

void UnInstallHookingFunc(void) {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)TrueSleep, Hooked_Sleep);
    DetourDetach(&(PVOID&)TrueGetLocalTime, Hooked_GetLocalTime);
    DetourTransactionCommit();
}