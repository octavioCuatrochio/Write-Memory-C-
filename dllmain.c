#include <Windows.h>

DWORD WINAPI MainThread(LPVOID param)
{
    while (true)
    {
        if (GetAsyncKeyState(VK_F6) & 0x80000)
        {
            MessageBoxA(NULL, "F6 pressed!", "F6 pressed!", MB_OK);
        }
    }
    return 0;
}

bool WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        MessageBoxA(NULL, "DLL injected!", "DLL injected!", MB_OK);
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    }
}