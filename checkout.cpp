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
  loadRentals(book, cardHolder);
  cout << "\033[2J\033[1;1H";

  do
  {
      printMenu();
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
  //int i = 0;
  string blank;
  Book * ptr = nullptr;

  inFile.open("books.txt");
  inFile >> id;

  while(inFile)
  {
    getline(inFile, blank);
    getline(inFile, title);
    getline(inFile, author);
    getline(inFile, subject);
    ptr = new Book(id, title, author, subject);
    b.push_back(ptr);
    inFile >> id;
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
  Person * ptr = nullptr;

  inFile.open("persons.txt");
  inFile >> id;

  while(inFile)
  {
    inFile >> active >> fName >> lName;
    ptr = new Person(id, active, fName, lName);
    cHolders.push_back(ptr);
    inFile >> id;


    i++;
  }
  id++;
  inFile.close();
  return id;
}

void loadRentals(vector <Book *> &b, vector <Person *> &cHolders)
{
  ifstream inFile;
  int bookID;
  int cardID;
  Book *book = nullptr;
  Person *card = nullptr;
  inFile.open("rentals.txt");

  inFile >> bookID;

  while(inFile)
  {
    inFile >> cardID;
    book = searchBook(b, bookID);
    card = searchPerson(cHolders, cardID);
    book->setPersonPtr(card);
    inFile >> bookID;
  }
  inFile.close();
}

void bookCheckout(vector <Book *> &b, vector <Person *> &cHolders)
{
  int cardID;
  int bookID;
  Person *card = nullptr;
  Book *book = nullptr;
  cout << "Please enter the card ID: ";
  cin.clear();
  cin >> cardID;
  cout << endl;
  card = searchPerson(cHolders, cardID);
  if(card==nullptr)
  {
  }
  else
  {
  cout << "Please enter the book ID:  ";
  cin.clear();
  cin >> bookID;
  cout << endl;
  book = searchBook(b, bookID);
    if(book == nullptr)
    {
      cout << "Invalid Entry.  Please try again." << endl;
    }
    else if(book->getPersonPtr() != nullptr)
    {
      cout << "Book is already checked out..." << endl;
    }
    else
    {
      book->setPersonPtr(card);
      cout << "Checkout Complete..." << endl;
    }
    cin.clear();
  }
}

void bookReturn(vector <Book *> &b, vector <Person *> &cHolders)
{
  int cardID;
  int bookID;
  Person *card = nullptr;
  Book *book = nullptr;
  cout << "Please enter the card ID: ";
  cin >> cardID;
  cout << endl;
  card = searchPerson(cHolders, cardID);
  cout << "Please enter the book ID:  " << endl;
  if(card==nullptr)
  {
  }
  else
  {
    cin >> bookID;
    cout << endl;
    book = searchBook(b, bookID);
    if(book==nullptr)
    {
    }
    else if(book->getPersonPtr() == nullptr)
    {
      cout << "Book is not checked out..." << endl;
    }
    else
    {
      book->setPersonPtr(nullptr);
      cout << "Return Complete..." << endl;
    }
  }
  cin.clear();
}

void viewBooks(vector <Book *> &b)
{
  cout << endl;
  for(int i = 0; i < b.size(); i++)
  {
    if(b.at(i)->getPersonPtr()==nullptr)
    {
      cout << "Book ID: " << b.at(i)->getBookID() << endl << "Title: " << b.at(i)->getTitle() << endl
      << "Author: " << b.at(i)->getAuthor() << endl << "Category: " << b.at(i)->getCategory()
      << endl << endl;
    }
  }
  cin.clear();
}

void viewRentals(vector <Book *> &b)
{
  cout << endl;
  for(int i = 0; i < b.size(); i++)
  {
    if(b.at(i)->getPersonPtr()!=nullptr)
    {
      cout << "Book ID: " << b.at(i)->getBookID() << endl << "Title: " << b.at(i)->getTitle() << endl
      << "Author: " << b.at(i)->getAuthor() << endl << "Category: " << b.at(i)->getCategory()
      << endl << endl;
    }
  }
  cin.clear();
}

void viewOutstanding(vector <Book *> &b, vector <Person *> &cHolders)
{
  int cardID;
  Person *card = nullptr;
  int count = 0;

  cout << "Please enter the card ID: ";
  cin >> cardID;
  cout << endl;
  card = searchPerson(cHolders, cardID);
  for(int i = 0; i < b.size(); i++)
  {
    if(b.at(i)->getPersonPtr()==card)
    {
      cout << "Book ID: " << b.at(i)->getBookID() << endl << "Title: " << b.at(i)->getTitle() << endl
      << "Author: " << b.at(i)->getAuthor() << endl << "Category: " << b.at(i)->getCategory()
      << endl << endl;
      count++;
    }
  }
  if(count == 0)
  {
    cout << "No books currently checked out..." << endl;
  }
  cin.clear();
}

int newCard(vector <Person *> &cHolders, int nextID)
{
  string first;
  string last;
  Person *card = nullptr;
  cout << "Please enter the first name:  ";
  cin >> first;
  cout << "Please enter the first name:  ";
  cin >> last;
  cout << endl;
  cHolders.push_back(new Person(nextID, true, first, last));
  card = searchPerson(cHolders, nextID);
  cout << "Card ID " << card->getCardID() << " is now active" << endl;

  nextID++;
  cin.clear();
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
  cout << endl;
  card = searchPerson(cHolders, cardID);
  if(card != nullptr)
  {
    if(card->getActive() == false)
    {
      cout << "Card ID is already inactive" << endl;
    }
    else
    {
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
  cin.clear();
}

void closeMenu(vector <Book *> &b, vector <Person *> &cHolders)
{
  ofstream rentals;
  ofstream persons;
  Person *card = nullptr;
  rentals.open("rentals.txt");
  for(int i = 0; i < b.size(); i++)
  {
    if(b.at(i)->getPersonPtr() != nullptr)
    {
      card = b.at(i)->getPersonPtr();
      if(card != nullptr)
      {
        rentals << b.at(i)->getBookID() << " " << card->getCardID() << endl;
      }
    }
    delete b.at(i);
  }
  rentals.close();
  persons.open("persons.txt");
  for(int i = 0; i < cHolders.size(); i++)
  {
    persons << cHolders.at(i)->getCardID() << " " << cHolders.at(i)->getActive() << " "
    << cHolders.at(i)->fullName() << endl;
    delete cHolders.at(i);
  }
  persons.close();
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
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
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
      cout << "Cardholder: " << cHolders.at(i)->fullName() << endl;
      return cPtr;
    }
  }
  cout << "Cardholder not found..." << endl;
  return nullptr;
}
