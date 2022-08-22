#include <stdio.h>

__declspec(dllexport) int add2(int num)
{
    return num + 2;
}

__declspec(dllexport) void printDLL()
{
    printf("hola desde el DLL!");
    return;
}