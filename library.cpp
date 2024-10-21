#include <iostream>
#include<iomanip>
#include<fstream>
#include<ctype.h>
#include<windows.h>
#include<limits>

#include "library.h"
#include "membertype.h"
#include "booktype.h"
#include "tree.h"
#include "treeM.h"
#include "options.h"

using namespace std;

string toUpper(string name)
{
    string temp = "";
for(char c : name)
temp += toupper(c);
return temp;
}
string capitalize(string name)
{
    string temporary = "";
    temporary = char(toupper(name[0]));
    for(int i = 1; i < name.length(); i++)
        temporary += char(tolower(name[i]));
    return temporary;
}

Library::Library(string booksFile, string membersFile)
{
    bookTxt = booksFile;
    memberTxt = membersFile;
    books.readFromFile(booksFile);
    member_size += members.readFromFile(membersFile);
}
void Library::displayBooks()
{
    system("cls");
    printTitle();
     books.display();
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
void Library::displayMembers()
{
    system("cls");
    printTitle();
    members.display();
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
void Library::borrowBook()
{
    string title;
    check:
    system("cls");
    printTitle();
    cout << left;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout <<setw(20)<< "\033[34mBook Title : \033[33m";
    getline(cin, title);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node<BookType> * book = books.search(toUpper(title));
    
    if(book) {
        book->data.print();
        BookType bookType = book->data;
        if(!bookType.isBorrowed()) {
            cout << "\033[34mEnter your member ID : \033[33m";
            int memberId;
            cin >> memberId;
            cout << "\033[0m" << endl;
            Node<MemberType> * member = members.search(memberId);
            if(member) {
                 cout << "\033[34mAre you sure you want to Borrow "<< bookType.getTitle() <<" book? (y/n) : \033[33m";
            string reply;
            cin >> reply;
            cout << "\033[0m" << endl;
            if(reply == "y" || reply == "Y") {
                books.writeToFile(bookTxt);
                book->data.setBorrowed(true);
                book->data.setBorrowerId(member->data.getId());
                cout << "\033[32mBook Successfully Borrowed\n"
                     << "\033[34mTo Borrow another book reply('y') :\033[33m ";
                cin >> reply;
                cout << "\033[0m" << endl;
                if(reply == "y" || reply == "Y")
                    goto check;
                
            }
        }else
         {
            string reply;
            cout << "\033[1;No Member By that Id "  << "\n"
                 << "\033[34mTo borrow another book reply('y') :\033[33m ";
            cin >> reply;
            cout << "\033[0m" << endl;
            if(reply == "y" || reply == "Y")
                goto check;
        }
      }else
       {    string reply;
            cout << "\033[31mThis book is already borrowed by member ID: " << bookType.getBorrowerId() << "\n"
                 << "\033[34mTo borrow another book reply('y') :\033[33m ";
            cin >> reply;
            cout << "\033[0m" << endl;
            if(reply == "y" || reply == "Y")
                goto check;
        }
    }else{
        string reply;
        cout << "\033[31mThis book is not found in the library\n"
             << "\033[34mTo borrow another book reply('y') :\033[33m ";
        cin >> reply;
        cout << "\033[0m" << endl;
        if(reply == "y" || reply == "Y")
            goto check;
    }
}
void Library::borrowedBooks()
{
    system("cls");
    printTitle();
    books.displayBorrowedBooks();
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
void Library::returnBook()
{
    string title;
    check:
    system("cls");
    printTitle();
    cout << left;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout <<setw(20)<< "\033[34mBook Title : \033[33m";
    getline(cin, title);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node<BookType> * book = books.search(toUpper(title));
    
    if(book) {
        book->data.print();
        BookType bookType = book->data;
        if(bookType.isBorrowed()) {
            cout << "\033[34mAre you sure you want to return "<< bookType.getTitle() <<" book? (y/n) : \033[33m";
            string reply;
            cin >> reply;
            cout << "\033[0m" << endl;
            if(reply == "y" || reply == "Y") {
                book->data.setBorrowed(false);
                book->data.setBorrowerId(-1);
                books.writeToFile(bookTxt);
                cout << "\033[32mBook Successfully Returned\n"
                     << "\033[34mTo return another book reply('y') :\033[33m ";
                cin >> reply;
                cout << "\033[0m" << endl;
                if(reply == "y" || reply == "Y")
                    goto check;
            
            }
        }else{
            string reply;
            cout << "\033[31mThis book is not borrowed by you\n"
                 << "\033[34mTo return another book reply('y') :\033[33m ";
            cin >> reply;
            cout << "\033[0m" << endl;
            if(reply == "y" || reply == "Y")
                goto check;
        }
 }else{
    string reply;
    cout << "\033[31mThis book is not found in the library\n"
         << "\033[34mTo return another book reply('y') :\033[33m ";
    cin >> reply;
    cout << "\033[0m" << endl;
    if(reply == "y" || reply == "Y")
        goto check;
 }
}
void Library::awaitBook()
{}
void Library::deleteBook()
{
    string title;
    check2:
    system("cls");
    printTitle();
    cout << left;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout <<setw(20)<< "\033[34mBook Name : \033[33m";
    getline(cin, title);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node<BookType> * book = books.search(toUpper(title));
    
    if(book) {
        book->data.print();
        BookType bookType = book->data;
        string reply;
        cout << "\033[34mAre you sure you want to delete "<< bookType.getTitle() <<" book? (y/n) : \033[33m";
        cin >> reply;
        cout << "\033[0m" << endl;
        if(reply == "y" || reply == "Y") {
            books.remove(bookType);
            books.writeToFile(bookTxt);
            cout << "\033[32mBook Successfully Deleted\n"
                     << "\033[34mTo delete another reply('y') :\033[33m ";
            cin >> reply;
            cout <<"\033[0m"<<endl;
            if(reply == "y" || reply == "Y")
                goto check2; 

        }
    
    }
    else {
        string reply;
        cout << "\033[31mBook not found\n"
                 << "\033[34mTo search again reply('y') :\033[33m ";
        cin >> reply;
        cout << "\033[0m" << endl;
        if(reply == "y" || reply == "Y")
            goto check2;
    }
}
    
void Library::deleteMember()
{
    int id;
    check3:
    system("cls");
    printTitle();
    cout << left;
    cout <<setw(20)<< "\033[34mMember Id : \033[33m";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node<MemberType> * member = members.search(id);
    
    if(member) {
        member->data.print();
        MemberType memberType = member->data;
        string reply;
        cout << "\033[34mAre you sure you want to delete this member? (y/n) : \033[33m";
        cin >> reply;
        cout << "\033[0m" << endl;
        if(reply == "y" || reply == "Y") 
        {
            members.remove(memberType);
            members.writeToFile(memberTxt);
            cout << "\033[32mMember Successfully Deleted\n"
                     << "\033[34mTo delete another reply('y') :\033[33m ";
            cin >> reply;
            cout <<"\033[0m"<<endl;
            if(reply == "y" || reply == "Y")
                goto check3;
        }
    }else
    {
        string reply;
        cout << "\033[31mMember not found\n"
                 << "\033[34mTo search again reply('y') :\033[33m ";
        cin >> reply;
        cout << "\033[0m" << endl;
        if(reply == "y" || reply == "Y")
            goto check3;
    }
}
void Library::addMember()
{
check1:
system("cls");
string firstName, lastName;
printTitle();
cout << left;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout <<setw(20)<< "\033[34mFirst Name : \033[33m";
getline(cin, firstName);
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout <<setw(20)<< "\033[34mLast Name : \033[33m";
getline(cin, lastName);
cin.ignore(numeric_limits<streamsize>::max(), '\n');

MemberType newMember(capitalize(firstName) + " " + capitalize(lastName), member_size++);
members.insert(newMember);
newMember.print();
cout << "\033[32mMember Successfully Added\n"
         << "\033[34mTo add another reply('y') :\033[33m ";
    string reply;
    cin >> reply;
    cout <<"\033[0m"<<endl;
    members.writeToFile(memberTxt);
    if(reply == "y" || reply == "Y")
        goto check1;

}
void Library::addBook()
{
string title, author, publisher;
double price;
int publicationYear;
check2:
system("cls");
printTitle();
cout << left;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout <<setw(20)<< "\033[34mBook Title : \033[33m";
getline(cin, title);
cin.ignore(numeric_limits<streamsize>::max(), '\n');
 Node<BookType> *temp = books.search(toUpper(title));
if(temp){
    cout << "\n\033[1;31mBooK is available\n"
         << "\033[34mTo add another reply('y') :\033[33m ";
    string reply;
    cin >> reply;
    cout <<"\033[0m"<<endl;
    if(reply == "y" || reply == "Y")
        goto check2;
}
else{
cout <<setw(20)<< "\033[34mBook Author : \033[33m";
getline(cin, author);
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout <<setw(20)<< "\033[34mBook Publisher : \033[33m";
getline(cin, publisher);
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout <<setw(20)<< "\033[34mBook Publisher year : \033[33m";
cin >> publicationYear;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
if (cin.fail())
    {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << " \033[1;31mINVALID INPUT!!\n ";
    goto check2;
    }
cout << endl << setw(20)<< "\033[34mBook Price : \033[33m";
cin >> price;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
if (cin.fail())
    {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << " \033[1;31mINVALID INPUT!!\n ";
    goto check2;
    }
 BookType newBook(toUpper(title),author,publisher,price,publicationYear);
 
 books.insert(newBook);
 newBook.print();
 cout << "\033[32mBook Successfully Added\n"
         << "\033[34mTo add another reply('y') :\033[33m ";
 books.writeToFile(bookTxt);
    string reply;
    cin >> reply;
    cout <<"\033[0m"<<endl;
    if(reply == "y" || reply == "Y")
        goto check2;
}

}
void Library::searchBook()
{
    string title;
    system("cls");
    printTitle();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\033[34mEnter book title to search : \033[33m";
    getline(cin, title);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node<BookType> * foundBook = books.search(toUpper(title));
    cout<< toUpper(title) << endl;
    if(foundBook){
        foundBook->data.print();
        if(!foundBook->data.isBorrowed()){
            cout << "\033[32m\n"
                    << "\033[34mDo You Want to Borrow "<< foundBook->data.getTitle()<< " reply('y') :\033[33m ";
                string reply;
                cin >> reply;
                cout <<"\033[0m"<<endl;
                if(reply == "y" || reply == "Y")
                {
                    cout << "\033[32m\n"
                    << "\033[34mInput Borrower Id :\033[33m ";
                    int id;
                    cin >> id;
                    cout <<"\033[0m"<<endl;
                    Node<MemberType> * borrower = members.search(id);
                    if(borrower)
                        {
                        foundBook->data.setBorrowerId(id);
                        foundBook->data.setBorrowed(true);
                        cout << "\033[32mBook Successfully Borrowed by "<< borrower->data.getTitle() <<"\n";
                        books.writeToFile(bookTxt);
                        }
                    else 
                       cout << "\033[1;31mBorrower not found\n";
                }

        }
    }
    else cout << "\033[1;31mBook not found\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
void Library::searchMember()
{
    int id;
    system("cls");
    printTitle();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\033[34mEnter member Id to search : \033[33m";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node<MemberType> * foundMember = members.search(id);
    if(foundMember!= nullptr){
        foundMember->data.print();
        cout << "\033[32mBorrowed Books\n";
        books.displayBorrowed(foundMember->data.getId());
    }
    else cout << "\033[1;31mMember not found\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
void Library::editMember()
{
    int id;
    system("cls");
    printTitle();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\033[34mEnter member Id to search : \033[33m";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node<MemberType> * foundMember = members.search(id);
    if(foundMember!= nullptr){
        foundMember->data.print();
        string firstName, lastName;
        cout << left;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<setw(20)<< "\033[34mFirst Name : \033[33m";
        getline(cin, firstName);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<setw(20)<< "\033[34mLast Name : \033[33m";
        getline(cin, lastName);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        foundMember->data.setName(capitalize(firstName) + " " + capitalize(lastName));
        cout << "\033[32mMember Successfully Updated\n";
        members.writeToFile(memberTxt);
        foundMember->data.print();
    }
    else cout << "\033[1;31mMember not found\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();

}
void Library::incrOrDecr(bool incrOrDecr)
{
    if(incrOrDecr)
        member_size++;
    else member_size--;       
}

void Library::options()
{
    system("CLS"); // Clear the console screen

    // Welcome message
    printLine('=');
    centerText("\033[32mWelcome to Abrehot\033[0m");
    centerText("\033[34mLibrary\033[0m");
    printLine('=');


    // Menu options
    std::cout << "\033[33mMenu:\033[0m\n";
    std::cout << "========================\n";
    std::cout << "1) Add Book\n";
    std::cout << "2) Add Member\n";
    std::cout << "3) Borrow Book\n";
    std::cout << "4) Borrowed Books\n";
    std::cout << "5) Delete Book\n";
    std::cout << "6) Display Books\n";
    std::cout << "7) Display Members\n";
    std::cout << "8) Edit Member Profile\n";
    std::cout << "9) Return Book\n";
    std::cout << "10) Search Book\n";
    std::cout << "11) Search Member\n";
    std::cout << "\033[31m12) Exit\033[0m\n";
    std::cout << "========================\n";
}

