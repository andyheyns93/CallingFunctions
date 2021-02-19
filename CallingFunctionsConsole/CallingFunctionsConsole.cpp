#include <Windows.h>
#include <iostream>
#include<string>


using std::cout;
using std::endl;

void FunctionCallWithoutParam()
{
	cout << "FunctionCallWithoutParam" << endl;
}

void FunctionCallWithParam(const char* string)
{
	cout << string << endl;
}

int main()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			FunctionCallWithoutParam();

			const char* param = "FunctionCallWithParam";
			FunctionCallWithParam(param);
		}
	}
	return 0;
}


