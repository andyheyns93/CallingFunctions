#include "pch.h"
#include <iostream>

using std::cout;
using std::endl;

//.text:00402400 callingfunctionsconsole.exe : $12400 #1800 < void __cdecl FunctionCallWithoutParam(void) >
typedef void(__cdecl* _FunctionCallWithoutParam)(void);
_FunctionCallWithoutParam FunctionCallWithoutParam;

//.text:00402380 callingfunctionsconsole.exe:$12380 #1780 <void __cdecl FunctionCallWithParam(char const *)>
typedef void(__cdecl* _FunctionCallWithParam)(char const*);
_FunctionCallWithParam FunctionCallWithParam;

DWORD WINAPI MainThread(LPVOID param)
{
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);

    // NOTE: offsets will be different each time 'callingfunctionsconsole.exe' is build!
    FunctionCallWithoutParam = (_FunctionCallWithoutParam)(moduleBase + 0x12400);
    FunctionCallWithParam = (_FunctionCallWithParam)(moduleBase + 0x12380);

    cout << "dll injected!" << endl;

    while (true)
    {
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            FunctionCallWithoutParam();
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            FunctionCallWithParam("Call it with function");
        }
        if (GetAsyncKeyState(VK_END) & 1)
        {
            cout << "dll ejected!" << endl;
            break;
        }
    }

    FreeLibraryAndExitThread((HMODULE)param, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

