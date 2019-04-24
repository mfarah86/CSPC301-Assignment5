#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "person.cpp"
#include "book.cpp"
using namespace std;

void printMenu();
void loadBooks(vector <Book *> &b);
int loadPersons(vector <Person *> &cHolders);
void loadRentals(vector <Book *> &b, vector <Person *> &cHolders);
void bookCheckout(vector <Book *> &b, vector <Person *> &cHolders);
void bookReturn(vector <Book *> &b, vector <Person *> &cHolders);
void viewBooks(vector <Book *> &b);
void viewRentals(vector <Book *> &b);
void viewOutstanding(vector <Book *> &b, vector <Person *> &cHolders);
int newCard(vector <Person *> &cHolders, int nextID);
void closeCard(vector <Book *> &b, vector <Person *> &cHolders);
void closeMenu(vector <Book *> &b, vector <Person *> &cHolders);
Book * searchBook(vector<Book *> myBooks, int id);
Person * searchPerson(vector <Person *> &cHolders, int id);

int main()
{
  vector<Book *> book;
  vector<Person *> cardHolder;
  int nextID;
  int choice;

  loadBooks(book);
  nextID = loadPersons(cardHolder);

  do
  {
      printMenu();
      cin.ignore();
      cin >> choice;
      switch(choice)
      {
          case 1:
              bookCheckout(book, cardHolder);
              break;

          case 2:
              bookReturn(book, cardHolder);
              break;

          case 3:
              viewBooks(book);
              break;

          case 4:
              viewRentals(book);
              break;

          case 5:
              viewOutstanding(book, cardHolder);
              break;

          case 6:
              nextID = newCard(cardHolder, nextID);
              break;

          case 7:
              closeCard(book, cardHolder);
              break;

          case 8:
              closeMenu(book, cardHolder);
              break;

          default:
              cout << "Invalid entry" << endl;
              break;
      }
      cout << endl;
  } while(choice != 8);

  return 0;
}

void printMenu()
{
  cout << "----------Library Book Rental System----------" << endl;
  cout << "1.  Book checkout" << endl;
  cout << "2.  Book return" << endl;
  cout << "3.  View all available books" << endl;
  cout << "4.  View all outstanding rentals" << endl;
  cout << "5.  View outstanding rentals for a cardholder" << endl;
  cout << "6.  Open new library card" << endl;
  cout << "7.  Close library card" << endl;
  cout << "8.  Exit system" << endl;
  cout << "Please enter a choice: ";
}

void loadBooks(vector<Book *> &b)
{
  ifstream inFile;
  int id;
  string title;
  string author;
  string subject;
  int i = 0;
  string blank;

  inFile.open("books.txt");
  inFile >> id;

  while(inFile)
  {
    getline(inFile, blank);
    getline(inFile, title);
    getline(inFile, author);
    getline(inFile, subject);
    b.at(i) = new Book(id, title, author, subject);
    b.push_back(b.at(i));

    cout << id << " " << title << " " << author << " " <<subject << endl;
     cout << b.at(i)->getBookID() << endl
     << b.at(i)->getTitle() << endl
     << b.at(i)->getAuthor() << endl
     << b.at(i)->getCategory() << endl;
    inFile >> id;
    i++;
  }
}

int loadPersons(vector<Person *> &cHolders)
{
  ifstream inFile;
  int id;
  bool active;
  string fName;
  string lName;
  int i = 0;

  inFile.open("persons.txt");
  inFile >> id;

  while(inFile)
  {
    inFile >> active >> fName >> lName;
    cHolders.at(i) = new Person(id, active, fName, lName);
    cHolders.push_back(cHolders.at(i));

    cout << cHolders.at(i)->getCardID() << " "
    << cHolders.at(i)->getActive() << " "
    << cHolders.at(i)->fullName() << endl;
    inFile >> id;


    i++;
  }
  id++;
  cout << id << endl;
  return id;
}

void loadRentals(vector <Book *> &b, vector <Person *> &cHolders)
{
  ifstream inFile;
  int bookID;
  int cardID;
  int checkBook;
  int checkCard;

  inFile >> bookID;

  while(inFile)
  {
    inFile >> cardID;
    Book *book = searchBook(b, bookID);
    Person *card = searchPerson(cHolders, cardID);
    book->setPersonPtr(card);
    inFile >> bookID;
  }
}

void bookCheckout(vector <Book *> &b, vector <Person *> &cHolders)
{
  int cardID;
  int bookID;
  cout << "Please enter the card ID: ";
  cin >> cardID;
  Person *card = searchPerson(cHolders, cardID);
  cout << card->fullName() << endl;
  cout << "Please enter the book ID:  " << endl;
  cin >> bookID;
  Book *book = searchBook(b, bookID);
  if(book->getPersonPtr() != nullptr)
  {
    cout << "Book is already checked out..." << endl;
  }
  else
  {
    book->setPersonPtr(card);
    cout << "You have checked out " << book->getTitle() << endl;
  }
}

void bookReturn(vector <Book *> &b, vector <Person *> &cHolders)
{
  int cardID;
  int bookID;
  cout << "Please enter the card ID: ";
  cin >> cardID;
  Person *card = searchPerson(cHolders, cardID);
  cout << card->fullName() << endl;
  cout << "Please enter the book ID:  " << endl;
  cin >> bookID;
  Book *book = searchBook(b, bookID);
  if(book->getPersonPtr() == nullptr)
  {
    cout << "Book is not checked out..." << endl;
  }
  else
  {
    book->setPersonPtr(nullptr);
    cout << "You have returned " << book->getTitle() << "..." << endl;
  }
}

void viewBooks(vector <Book *> &b)
{
  for(int i = 0; i < b.size(); i++)
  {
    if(b.at(i)->getPersonPtr()==nullptr)
    {
      cout << "Book ID: " << b.at(i)->getBookID() << "Title: " << b.at(i)->getTitle() << endl
      << "Author: " << b.at(i)->getAuthor() << endl << "Category: " << b.at(i)->getCategory()
      << endl << endl;
    }
  }
}

void viewRentals(vector <Book *> &b)
{
  for(int i = 0; i < b.size(); i++)
  {
    if(b.at(i)->getPersonPtr()!=nullptr)
    {
      cout << "Book ID: " << b.at(i)->getBookID() << "Title: " << b.at(i)->getTitle() << endl
      << "Author: " << b.at(i)->getAuthor() << endl << "Category: " << b.at(i)->getCategory()
      << endl << endl;
    }
  }
}

void viewOutstanding(vector <Book *> &b, vector <Person *> &cHolders)
{
  int cardID;
  Person *card = nullptr;
  int count = 0;

  cout << "Please enter the card ID: ";
  cin >> cardID;
  card = searchPerson(cHolders, cardID);
  cout << "Cardholder: " << endl;
  for(int i = 0; i < b.size(); i++)
  {
    if(b.at(i)->getPersonPtr()==card)
    {
      cout << "Book ID: " << b.at(i)->getBookID() << "Title: " << b.at(i)->getTitle() << endl
      << "Author: " << b.at(i)->getAuthor() << endl << "Category: " << b.at(i)->getCategory()
      << endl << endl;
      count++;
    }
  }
  if(count == 0)
  {
    cout << "No books currently checked out..." << endl;
  }
}

int newCard(vector <Person *> &cHolders, int nextID)
{
  string first;
  string last;
  cout << "Please enter the first name:  ";
  cin >> first;
  cout << "Please enter the first name:  ";
  cin >> last;
  cHolders.push_back(new Person(nextID, true, first, last));
  nextID++;
  return nextID;
}

void closeCard(vector <Book *> &b, vector <Person *> &cHolders)
{
  char choice;
  int cardID;
  int count = 0;
  Person * card = nullptr;
  cout << "Please enter the card ID: ";
  cin >> cardID;
  card = searchPerson(cHolders, cardID);
  if(card != nullptr)
  {
    if(card->getActive() == false)
    {
      cout << "Card ID is already inactive" << endl;
    }
    else
    {
      cout << "Cardholder: " << endl;
      for(int i = 0; i < b.size(); i++)
      {
        if(b.at(i)->getPersonPtr()==card)
        {
          cout << "Book ID: " << b.at(i)->getBookID() << "Title: " << b.at(i)->getTitle() << endl
          << "Author: " << b.at(i)->getAuthor() << endl << "Category: " << b.at(i)->getCategory()
          << endl << endl;
          count++;
        }
      }
      if(count!=0)
      {
        cout << "Please return the above books..." << endl;
      }
      else
      {
        cout << "Are you sure you want to deactivate card (y/n)? ";
        cin >> choice;
        if (choice == 'y')
        {
          card->setActive(false);
          cout << "Card ID deactivated" << endl;
        }
        else
        {
          cout << "Card ID status unchanged" << endl;
        }
      }
    }
  }
}

void closeMenu(vector <Book *> &b, vector <Person *> &cHolders)
{
  ofstream rentals("rentals.txt");
  ofstream persons("persons.txt");
  Person *card = nullptr;
  for(int i = 0; i < b.size(); i++)
  {
    if(b.at(i)->getPersonPtr() != nullptr)
    {
      card = b.at(i)->getPersonPtr();
      rentals << b.at(i)->getBookID() << " " << card->getCardID() << endl;
    }
    delete b.at(i);
  }
  for(int i = 0; i < cHolders.size(); i++)
  {
    persons << cHolders.at(i)->getCardID() << " " << cHolders.at(i)->getActive() << " "
    << cHolders.at(i)->fullName() << endl;
    delete cHolders.at(i);
  }
}

Book * searchBook(vector<Book *> myBooks, int id)
{
  Book * bPtr;
  int bID;
  for(int i = 0; i < myBooks.size(); i++)
  {
    bID = myBooks.at(i)->getBookID();
    if(bID == id)
    {
      bPtr = myBooks.at(i);
      return bPtr;
    }
  }
  cout << "Book not found..." << endl;
  return nullptr;
}
Person * searchPerson(vector <Person *> &cHolders, int id)
{
  Person * cPtr;
  int cID;
  for(int i = 0; i < cHolders.size(); i++)
  {
    cID = cHolders.at(i)->getCardID();
    if(cID == id)
    {
      cPtr = cHolders.at(i);
      return cPtr;
    }
  }
  cout << "Cardholder not found..." << endl;
  return nullptr;
}
