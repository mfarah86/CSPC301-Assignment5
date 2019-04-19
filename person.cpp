#include <iostream>
#include "person.h"
using namespace std;

Person::Person(int cID, bool pActive, string fName, string lName)
{
  cardID = cID;
  active = pActive;
  firstName = fName;
  lastName = lName;
}

int Person::getCardID()
{
  return cardID;
}

void Person::setActive(bool pActive)
{
  active = pActive;
}

bool Person::getActive()
{
  return active;
}

string Person::getFirstName()
{
  return firstName;
}

string Person::getLastName()
{
  return lastName;
}

string Person::fullName()
{
  string fullName = firstName + " " + lastName;
  return lastName;
}
