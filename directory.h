
#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <vector>
#include <ctime>
#include <time.h>
#include "file.h"

using namespace std;

class Directory
{
private:
	string name;
	int numFiles;
	Directory * parent = NULL;
	Directory * previous = NULL;
	vector<File> content;
	string owner;
	string group;
	string publc; //public
	time_t result;

public:

	Directory() :name("\\"), numFiles(0), owner("111"), group("111"), publc("111"){};

	Directory(string n) :name(n), numFiles(0), owner("111"), group("111"), publc("111"){};

	string getName(){ return name; };
	void setName(string n){ name = n; };
	int getNumFiles() { return numFiles; };
	int vectSize() const { return content.size(); };

	Directory& runCommand(string command, string & line);

	void addFile(string n);
	void removeFile(string n);

	void addDirectory(string n);
	void removeDirectory(string n);

	void conversion(string line);

	void printContents();
	void longPrint();
	string getDirectoryChain();

	bool duplicateCheckDirc(string line);
	bool duplicateCheckFile(string line);
	int matchFindDirc(string line);
	int matchFindFile(string line);

	string printPath(Directory * d);

	~Directory();
};

#endif
