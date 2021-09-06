#include "pch.h"
HINSTANCE g_hinstance = NULL;

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    if (DetourIsHelperProcess()) {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH) {
        DetourRestoreAfterWith();
        InstallHookingFunc();
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        UnInstallHookingFunc();
    }
    return TRUE;
}

