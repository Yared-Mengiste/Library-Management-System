#ifndef BOOKTYPE_H
#define BOOKTYPE_H

#include <string>

class BookType {
public:
    BookType();
    BookType(std::string title, std::string author, std::string publisher, double price, int pubYear, bool borrowed = false, int borrower_id = -1);

    void print() const;
    void setTitle(std::string t);
    void setAuthor(std::string authorh);
    void setPublisher(std::string);
    void setPrice(double);
    void setPubYear(int);
    void setBorrowed(bool);
    void setBorrowerId(int);

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    double getPrice() const;
    int getPubYear() const;
    bool isBorrowed() const;
    int getBorrowerId() const;

private:
    std::string title;
    std::string author;
    std::string publisher;
    double price;
    int pubYear;
    bool borrowed;
    int borrower_id;
};

#endif // BOOKTYPE_H
