#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
using namespace std;

class Person
{
private:
  int cardID;
  bool active;
  string firstName;
  string lastName;

public:
  Person(int pCID, bool pActive, string fName, string lName);
  int getCardID();
  void setActive(bool act);
  bool getActive();
  string getFirstName();
  string getLastName();
  string fullName();
};
#endif
