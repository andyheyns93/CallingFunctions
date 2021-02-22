#include "PersonRepository.h"
#include <list>
#include "Person.h"

list<Person> PersonRepository::GetAllPersons() {
	list<Person> listOfPersons;

	Person person1("John", "Doe", 1990);
	listOfPersons.push_back(person1);

	Person person2("Jane", "Doe", 1995);
	listOfPersons.push_back(person2);

	return listOfPersons;
}
Person PersonRepository::GetFirstPerson() {
	Person person("John", "Doe", 1990);
	return person;
}