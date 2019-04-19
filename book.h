#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "person.h"
using namespace std;

class Book
{
private:
  int bookID;
  string title;
  string author;
  string category;
  Person * personPtr = nullptr;

public:
  Book(int bID, string bTitle, string bAuthor, string bCategory);
  int getBookID();
  string getTitle();
  string getAuthor();
  string getCategory();
  void *setPersonPtr(Person * ptr);
  Person * getPersonPtr();
};
#endif
