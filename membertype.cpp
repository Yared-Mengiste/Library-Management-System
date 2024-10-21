#include<iostream>
#include<iomanip>
#include<ctype.h>

#include"membertype.h"


MemberType::MemberType():name(""),id(-1){}
MemberType::MemberType(string name, int id):name(name),id(id) {}
void MemberType::setName(string n){name = n;}
void MemberType::setI(int n){id = n;}
void MemberType::print()
{
        std::cout << std::left;
        std::cout <<  "\033[36m---------------------------------------------------------------------------\n"
         << "\033[34m" <<setw(25)<< "ID:\033[33m " << id << std::endl
         <<  "\033[36m---------------------------------------------------------------------------\033[36m\n"
         <<"\033[34m" <<setw(25)<< "Member Name:\033[33m"<<name<<std::endl<<std::endl
         <<  "\033[35m---------------------------------------------------------------------------\033[0m\n\n";   
}
int MemberType::getId() const{return id;}
string MemberType::getTitle() const{return name;}



 