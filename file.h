#ifndef FILE_H
#define FILE_H

#include <iostream>

using namespace std;

class File
{
private:
	int sizeF;
	string name;
	string owner;
	string group;
	string publc; //public

public:
	time_t result;
	File(string n) : sizeF(rand()%1024), name(n), owner("111"), group("111"), publc("111"){};
	int getSizeF(){ return sizeF; };
	void setName(string n){ name = n; };
	string getName(){ return name; };
	string getOwner(){ return owner; };
	string getGroup(){ return group; };
	string getPublc(){ return publc; };
	void conversion(string line);

	friend std::ostream& operator<< (std::ostream& out, const File& f);
};

#endif
