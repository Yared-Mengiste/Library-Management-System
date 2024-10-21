#include <iostream>
#include<iomanip>
#include<ctype.h>
#include "bookType.h"


BookType::BookType() 
    : title(""), author(""), publisher(""), price(0.0), pubYear(0), borrowed(false), borrower_id(-1) {}

BookType::BookType(std::string title, std::string author, std::string publisher, double price, int pubYear, bool borrowed, int borrower_id)
    : title(title), author(author), publisher(publisher), price(price), pubYear(pubYear), borrowed(borrowed), borrower_id(borrower_id) {}

void BookType::print() const {
        std::cout << std::left;
        std::cout <<  "\033[36m---------------------------------------------------------------------------\n"
         << "\033[34m" <<std::setw(25)<< "Title:\033[33m " << title << std::endl
         <<  "\033[36m---------------------------------------------------------------------------\033[36m\n"
         <<"\033[34m" <<std::setw(25)<< "Author:\033[33m"<<author<<std::endl<<std::endl
         <<"\033[34m" <<std::setw(25)<< "Borrowed:\033[33m"<<(borrowed ? "Yes" : "No")<<std::endl<<std::endl
         <<"\033[34m" <<std::setw(25)<< "Borrower ID:\033[33m"<<borrower_id<<std::endl
         <<  "\033[35m---------------------------------------------------------------------------\033[0m\n\n";

}

void BookType::setTitle(std::string t) { title = t; }
void BookType::setAuthor(std::string authorh) { author = authorh; }
void BookType::setPublisher(std::string p) { publisher = p; }
void BookType::setPrice(double p) { price = p; }
void BookType::setPubYear(int y) { pubYear = y; }
void BookType::setBorrowed(bool b) { borrowed = b; }
void BookType::setBorrowerId(int id) { borrower_id = id; }

std::string BookType::getTitle() const { return title; }
std::string BookType::getAuthor() const { return author; }
std::string BookType::getPublisher() const { return publisher; }
double BookType::getPrice() const { return price; }
int BookType::getPubYear() const { return pubYear; }
bool BookType::isBorrowed() const { return borrowed; }
int BookType::getBorrowerId() const { return borrower_id; }
