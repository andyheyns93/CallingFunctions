#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include "Person.h"

using std::cout;
using std::endl;
using std::string;
using std::list;

//.text:00095E80 callingfunctionsconsole.exe:$15E80 #5280 <void __cdecl PrintAllPersons(void)>
typedef void(__stdcall* _PrintAllPersons)(void);
_PrintAllPersons PrintAllPersons;

//.text:00095E00 callingfunctionsconsole.exe:$15E00 #5200 <void __cdecl FunctionCallWithoutParam(void)>
typedef void(__stdcall* _FunctionCallWithoutParam)(void);
_FunctionCallWithoutParam FunctionCallWithoutParam;

//.text:00095D30 callingfunctionsconsole.exe:$15D30 #5130 <void __cdecl FunctionCallWithParam(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >)>
typedef void(__stdcall* _FunctionCallWithParam)(string);
_FunctionCallWithParam FunctionCallWithParam;

//.text:00099560 callingfunctionsconsole.exe:$19560 #8960 <public: class std::list<class Person,class std::allocator<class Person> > __thiscall PersonRepository::GetAllPersons(void)>
typedef list<Person>(__stdcall* _PersonRepositoryGetAllPersons)(void);
_PersonRepositoryGetAllPersons PersonRepositoryGetAllPersons;

//.text:000997E0 callingfunctionsconsole.exe:$197E0 #8BE0 <public: class Person __thiscall PersonRepository::GetFirstPerson(void)>
typedef Person(__stdcall* _PersonRepositoryGetFirstPerson)(void);
_PersonRepositoryGetFirstPerson PersonRepositoryGetFirstPerson;

DWORD WINAPI MainThread(LPVOID param)
{
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);

    // NOTE: offsets will be different each time 'callingfunctionsconsole.exe' is build!
    PrintAllPersons = (_PrintAllPersons)(moduleBase + 0x15E80);
    FunctionCallWithoutParam = (_FunctionCallWithoutParam)(moduleBase + 0x15E00);
    FunctionCallWithParam = (_FunctionCallWithParam)(moduleBase + 0x15D30);
    PersonRepositoryGetAllPersons = (_PersonRepositoryGetAllPersons)(moduleBase + 0x19560);
    PersonRepositoryGetFirstPerson = (_PersonRepositoryGetFirstPerson)(moduleBase + 0x197E0);

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
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            PrintAllPersons();
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            list<Person> persons = PersonRepositoryGetAllPersons();

            list<Person>::iterator it;
            for (it = persons.begin(); it != persons.end(); ++it) {
                cout << it->LastName << " " << it->FirstName << " - " << it->Age << endl;
            }
        }
        if (GetAsyncKeyState(VK_NUMPAD6) & 1)
        {
            Person p = PersonRepositoryGetFirstPerson();

            cout << "--First Person--" << endl;
            cout << p.LastName << " " << p.FirstName << " - " << p.Age << endl;
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

