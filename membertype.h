#ifndef MEMBERTYPE_H
#define MEMBERTYPE_H

#include<string>
#include "booktype.h"
using namespace std;
class MemberType
{
public:
MemberType();
MemberType(string name, int id);
void setName(string n);
void setI(int n);
void print(); 
int getId()const;
string getTitle()const;
private:
string name;
int id;
};
#endif