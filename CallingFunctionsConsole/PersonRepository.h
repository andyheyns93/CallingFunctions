#pragma once

#include <list>
#include "Person.h"

using std::list;

class PersonRepository
{
	public:
		list<Person> GetAllPersons();
		Person GetFirstPerson();
};

