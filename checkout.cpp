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
void viewBooks(vector <Book *> &b, vector <Person *> &cHolders);
void viewRentals(vector <Book *> &b, vector <Person *> &cHolders);
void viewOutstanding(vector <Book *> &b, vector <Person *> &cHolders);
void newCard(vector <Person *> &cHolders, int nextID);
void closeCard(vector <Book *> &b, vector <Person *> &cHolders);
void closeMenu();
void updatePersons(vector <Book *> &b, vector <Person *> &cHolders);
void updateRentals(vector <Book *> &b, vector <Person *> &cHolders);
Book * searchBook(vector<Book *> myBooks, int id);

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
              viewBooks(book, cardHolder);
              break;

          case 4:
              viewRentals(book, cardHolder);
              break;

          case 5:
              viewOutstanding(book, cardHolder);
              break;

          case 6:
              newCard(cardHolder, nextID);
              break;

          case 7:
              closeCard(book, cardHolder);
              break;

          case 8:
              closeMenu();
              break;

          default:
              cout << "Invalid entry" << endl;
              break;
      }
      cout << endl;
 } while(choice != 8);

 delete book;//make a loop that deletes every pointer in the vector
 delete cardHolder;//make a loop that deletes every pointer in the vector


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
    for(int i = 0; i < b.size(); i++)
    {
      checkBook = b.at(i)->getBookID();
      if(bookID == checkBook)
      {
        for(int j = 0; j < cHolders.size(); j ++)
        {
          checkCard = cHolders.at(i)->getCardID();
          if(checkCard == cardID)
          {
            b.at(i)->setPersonPtr(cHolders.at(i));
            break;
          }
        }
        break;
      }
    }
    inFile >> bookID;
  }
}

void bookCheckout(vector <Book *> &b, vector <Person *> &cHolders)
{
  int cardID;
  int checkCard;
  int bookID;
  int checkBook;
  cout << "Please enter the card ID: ";
  cin >> cardID;
  for(int i = 0; i < cHolders.size(); i++)
  {
    checkCard = cHolders.at(i)->getCardID();
    if(checkCard == cardID)
    {
      cout << cHolders.at(i)->fullName() << endl;
      cout << "Please enter the book ID" << endl;
      cin >> bookID;
      for(int j = 0; j < b.size(); j++)
      {
        checkBook = b.at(j)->getBookID();
        if(checkBook == bookID)
        {
          if(b.at(j)->getPersonPtr() != nullptr)
          {
            cout << "Book already checked out..." << endl;
          }
          else
          {
            b.at(j)->setPersonPtr(cHolders.at(i));
            cout << b.at(j)->getTitle() << endl << "Rental Completed...";
          }
        }
        else if(checkBook == b.size())
        {
          cout << "Book ID not found..." << endl;
        }
        else
        {

        }
      }
    }
    else if(checkCard == cHolders.size())
    {
      cout << "Card ID not found..." << endl;
    }
    else
    {

    }
  }
}

void bookReturn(vector <Book *> &b, vector <Person *> &cHolders)
{

}

void viewBooks(vector <Book *> &b, vector <Person *> &cHolders)
{

}

void viewRentals(vector <Book *> &b, vector <Person *> &cHolders)
{

}

void viewOutstanding(vector <Book *> &b, vector <Person *> &cHolders)
{

}

void newCard(vector <Person *> &cHolders, int nextID)
{

}

void closeCard(vector <Book *> &b, vector <Person *> &cHolders)
{

}

void closeMenu()
{

}

void updatePersons(vector <Book *> &b, vector <Person *> &cHolders)
{

}

void updateRentals(vector <Book *> &b, vector <Person *> &cHolders)
{

}

Book * searchBook(vector<Book *> myBooks, int id)
{
  return nullptr;
}
