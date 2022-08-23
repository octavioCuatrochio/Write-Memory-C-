
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main(int argc, char const *argv[])
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process.

    char *exeString = "C:\\Users\\Suministros\\Desktop\\C\\cosa\\dummy.exe";

    if (!CreateProcess(exeString, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 0;
    }

    HANDLE hProcess = pi.hProcess;

    printf("Notepad con id: %lu \n", pi.dwProcessId);

    char dll[] = "dllmain.dll";
    char dllPath[MAX_PATH] = {0};
    GetFullPathName(dll, MAX_PATH, dllPath, NULL);

    printf("path: %s", dllPath);

    // HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, TRUE, pID);
    LPVOID pszLibFileRemote = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    WriteProcessMemory(hProcess, pszLibFileRemote, dllPath, strlen(dllPath) + 1, NULL);
    HANDLE handleThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, pszLibFileRemote, 0, NULL);

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(hProcess);
    CloseHandle(handleThread);
    VirtualFreeEx(hProcess, dllPath, 0, MEM_RELEASE);
    CloseHandle(pi.hThread);
    return 0;
}
