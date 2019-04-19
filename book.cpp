#include <iostream>
#include <string>
#include "book.h"
using namespace std;

Book::Book(int bID, string bTitle, string bAuthor, string bCategory)
{
  bookID = bID;
  title = bTitle;
  author = bAuthor;
  category = bCategory;
  personPtr;
}

int Book::getBookID()
{
  return bookID;
}

string Book::getTitle()
{
  return title;
}

string Book::getAuthor()
{
  return author;
}

string Book::getCategory()
{
  return category;
}

void * Book::setPersonPtr(Person * ptr)
{
  personPtr = ptr;
}

Person * Book::getPersonPtr()
{
  return personPtr;
}
