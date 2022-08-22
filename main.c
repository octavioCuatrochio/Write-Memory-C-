#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <Windows.h>
#include <ntstatus.h>
#include <tlhelp32.h>
#include <memoryapi.h>

DWORD getProcID(char *procName)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    DWORD result = 0;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hProcessSnap)
        return (FALSE);

    pe32.dwSize = sizeof(PROCESSENTRY32); // <----- IMPORTANT

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap); // clean the snapshot object
        printf("!!! Failed to gather information on system processes! \n");
        return (0);
    }

    do
    {
        // printf("Checking process %ls\n", pe32.szExeFile);
        if (0 == strcmp(procName, pe32.szExeFile))
        {
            result = pe32.th32ProcessID;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    return result;
}

void alert(char *text)
{
    MessageBoxA(NULL, text, text, MB_OK);
}

int main(int argc, char const *argv[])
{
    char *procName = "notepad.exe";
    DWORD pID = getProcID(procName);

    printf("Notepad con id: %lu", pID);

    HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, TRUE, pID);
    // LPVOID pszLibFileRemote = VirtualAllocEx(hProcess, NULL, )

    alert("PRuebaaaa");
    return 0;
}
