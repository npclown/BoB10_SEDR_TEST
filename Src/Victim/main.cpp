#include "stdafx.h"

int main(void)
{
    SYSTEMTIME stTime;
    GetLocalTime(&stTime);

    printf("%04d-%02d-%02d %02d:%02d:%02d\n",
        stTime.wYear, stTime.wMonth, stTime.wDay,
        stTime.wHour, stTime.wMinute, stTime.wSecond);

    Sleep(1000);
    return 0;
}
