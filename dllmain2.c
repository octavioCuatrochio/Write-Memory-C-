#include <Windows.h>
#include <stdbool.h>

HANDLE masterHandle = NULL;
byte value = 0;

DWORD WINAPI MainThread(LPVOID param)
{
    while (true)
    {
        if (GetAsyncKeyState(VK_F6) & 0x80000)
        {
            ReadProcessMemory(masterHandle, (void *)0x7400, &value, 4, 0);
            MessageBoxA(NULL, "F6 pressed!", "F6 pressed!", MB_OK);
            unsigned char *p = (unsigned char *)&value;
            MessageBoxA(NULL, p, p, MB_OK);
        }
        Sleep(100);
    }
    return 0;
}

bool WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        masterHandle = GetCurrentProcess();
        MessageBoxA(NULL, "DLL injected!", "DLL injected!", MB_OK);
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    }
}