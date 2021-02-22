#include "Person.h"
#include <string>

using std::string;

Person::Person(string firstName, string lastName, int age) {
    FirstName = firstName;
    LastName = lastName;
    Age = age;
}