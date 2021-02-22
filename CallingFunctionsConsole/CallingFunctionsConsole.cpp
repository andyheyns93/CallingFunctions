#include <Windows.h>
#include <iostream>
#include <string>
#include <list>

#include "PersonRepository.h"
#include "Person.h"

using std::cout;
using std::endl;
using std::string;

void PrintAllPersons() {
	
	PersonRepository rep;
	list<Person> persons = rep.GetAllPersons();

	list<Person>::iterator it;
	for (it = persons.begin(); it != persons.end(); ++it) {
		cout << it->FirstName <<  " " << it->LastName << " - " << it->Age << endl;
	}
}

void FunctionCallWithoutParam()
{
	cout << "FunctionCallWithoutParam" << endl;
}

void FunctionCallWithParam(string textToPrint)
{
	cout << textToPrint << endl;
}

int main()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			FunctionCallWithoutParam();
			FunctionCallWithParam("FunctionCallWithParam");
			PrintAllPersons();
		}
	}
	return 0;
}


