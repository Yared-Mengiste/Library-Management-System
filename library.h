#ifndef LIBRARY_H
#define LIBRARY_H


#include <iostream>
#include "booktype.h"
#include "membertype.h"
#include "tree.h"
#include "treeM.h"

class Library{
    private:
        Tree<BookType> books;
        TreeM<MemberType> members;
        string bookTxt, memberTxt;
        int member_size = 1000;
    public:
        void options();
        Library(string booksFile, string membersFile);
        void borrowBook();
        void borrowedBooks();
        void returnBook();
        void awaitBook();
        void deleteBook();
        void editMember();
        void deleteMember();
        void addMember();
        void addBook();
        void searchBook();
        void searchMember();
        void incrOrDecr(bool incrOrDecr);
        void displayMembers();
        void displayBooks();
        

};

#endif 