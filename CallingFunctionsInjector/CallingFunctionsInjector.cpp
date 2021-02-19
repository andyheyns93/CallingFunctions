#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Shlwapi.h>

DWORD GetProcessId(const char* processName)
{
    DWORD processId = 0;
    HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (handleSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(processEntry);

        if (Process32First(handleSnapshot, &processEntry))
        {
            do
            {
                if (!_stricmp(processEntry.szExeFile, processName))
                {
                    processId = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(handleSnapshot, &processEntry));
        }
    }
    CloseHandle(handleSnapshot);
    return processId;
}

std::string ExtractDirectory(const std::string& path)
{
    return path.substr(0, path.find_last_of('\\') + 1);
}

int main()
{
    char ownPth[MAX_PATH];
    HMODULE hModule = GetModuleHandle(NULL);
    GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));

    std::string directory = ExtractDirectory(std::string(ownPth));
    std::string dllName("CallingFunctionsHook.dll");
    dllName.insert(0, directory);

    const char* dllInject = const_cast<char*>(dllName.c_str());
    const char* processName = "CallingFunctionsConsole.exe";
    DWORD processId = 0;

    while (!processId)
    {
        processId = GetProcessId(processName);
    }

    HANDLE handleProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);

    if (handleProcess && handleProcess != INVALID_HANDLE_VALUE)
    {
        void* virtualAlloc = VirtualAllocEx(handleProcess, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (virtualAlloc)
        {
            WriteProcessMemory(handleProcess, virtualAlloc, dllInject, strlen(dllInject) + 1, 0);
        }

        HANDLE handleThread = CreateRemoteThread(handleProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, virtualAlloc, 0, 0);

        if (handleThread) {
            CloseHandle(handleThread);
        }
    }
    if (handleProcess) {
        CloseHandle(handleProcess);
    }
    return 0;
}
