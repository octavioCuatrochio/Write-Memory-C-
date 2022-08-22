#include <windows.h>

int main(int argc, char const *argv[])
{
    HMODULE hModule = LoadLibrary("compiled.dll");
    FARPROC a = GetProcAddress(hModule, "printDLL");
    a();
    return 0;
}
