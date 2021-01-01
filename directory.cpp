#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <chrono>

#include "directory.h"
#include "file.h"
#include "functions.h"

/*
Creates new File with the name "line" and random size from 0 to 1023
and adds it to the current Directory.
*/
void Directory::addFile(string line)
{
	File f(line);
	f.result = time(NULL);
	//f.sizeF = rand() % 1024;
	content.push_back(f);
}

/*
Removes the File with the name "line" and returns error message if the
file cannot be found.
*/
void Directory::removeFile(string line)
{
	int vect_size = content.size();
	bool found = false;
	int i = 0;

	if(line == "")
	{
	    cout << "Error, no parameter given." << endl;
	    return;
    }

	do
	{
		if (content[i].getName() != line)
			i++;
		else
			found = true;
	} while (found == false && i < vect_size);

	if (found == true)
		content.erase(content.begin() + i);
	else
		cout << "Error, file not found." << endl;
}

/*
Creates a new Directory with the name "line" and adds it to the
current Directory. If the current Directory has no parent, the
parent is set equal to the new Directory. Otherwise, the new
Directory is given it's parent's permissions.
*/
void Directory::addDirectory(string line)
{
	if (parent == NULL)
	{
		parent = new Directory[1];
		parent->result = time(NULL);
		parent[0].setName(line);
		numFiles++;
		parent[0].previous = this;
	}
	else
	{
		Directory * tmp = new Directory[numFiles + 1];
		for (int i = 0; i < numFiles; i++)
		{
			tmp[i] = parent[i];
			tmp[i].previous = parent[i].previous;
			tmp[i].owner = parent[i].owner;
			tmp[i].group = parent[i].group;
			tmp[i].publc = parent[i].publc;
		}

		delete[] parent;
		tmp[numFiles].setName(line);
		tmp[numFiles].result = time(NULL);
		parent[numFiles].previous = this;
		numFiles++;
		parent = tmp;
		tmp = NULL;
	}
}

/*
Removes the Directory with name "line" if it can be found.
Deallocates the Directory's files as well.
*/
void Directory::removeDirectory(string line)
{
	int i = 0;
	bool found = false;
	if(line == "")
	{
	    cout << "Error, no parameter given." << endl;
	    return;
    }
	string tmp;

	do
	{
	    tmp = parent[i].getName();
		if (tmp == line)
			found = true;
		else
			i++;
	} while (tmp != line && i < numFiles);
	if (!found)
	{
		cout << "Could not delete file, it does not exist." << endl;
		return;
	}
	else
	{
		Directory * holder = new Directory[numFiles - 1];
		int control = 0;
		for (int j = 0; j < numFiles; j++)
		{
			if (j != i)
			{
				holder[control] = parent[j];
				control++;
			}
		}
		delete[] parent;
		parent = holder;
		holder = NULL;
		numFiles--;
	}
}

/*
Directory Destructor, deletes Directory's parents
*/
Directory::~Directory()
{
	if (parent != NULL)
	{
		delete[] parent;
		parent = NULL;
		previous = NULL;
		numFiles = 0;
	}
}

/*
Runs mkdir, rm, touch, cd.., cd../, ls, ls -line, and chmod.
(pwd, exit, and quit handled in main) Returns error messages
if file names are not valid, folders cannot be found, or if
commands are not recognized.
*/
Directory& Directory::runCommand(string command, string & line)
{
	if (command == "mkdir")
	{
		if (!line.empty() && !duplicateCheckDirc(line))
			this->addDirectory(line);
		else
			cout << "Error:Not a valid file name." << endl;
	}

	else if (command == "rmdir")
		this->removeDirectory(line);

	else if (command == "rm")
		this->removeFile(line);

	else if (command == "touch")
	{
		if (!line.empty() && !duplicateCheckFile(line))
			this->addFile(line);
		else
			cout << "Error:Not a valid file name." << endl;
	}

	else if (command == "cd")
	{
		if (!line.empty() && duplicateCheckDirc(line))
			return parent[this->matchFindDirc(line)];
		else if (line == ".." || line == "../")
			return *previous;
		else
			cout << "Folder does not exist." << endl;
	}

	else if (command == "ls")
	{
		if (fetchFlags(line))
			this->longPrint();
		else
			this->printContents();
	}

	else if (command == "chmod")
	{
		string numbers = fetchCommand(line);
		if (validCHMOD(numbers))
		{
			if (this->duplicateCheckDirc(line))
				parent[this->matchFindDirc(line)].conversion(numbers);
			else if (this->duplicateCheckFile(line))
				content[this->matchFindFile(line)].conversion(numbers);
			else
				cout << "Could not find item " << line << "." << endl;
		}
		else
			cout << "Invalid parameters for command \"chmod\"." << endl;
	}

	else if (command != "quit" && command != "exit")
		cout << "Command " << command << " is not recognized." << endl;

	return *this;
}

/*
Prints the names of each File and Directory in the current
Directory, and nothing more. Used for the "ls" command
*/
void Directory::printContents()
{
	int vect_size = this->vectSize();
	for (int i = 0; i<numFiles; i++)
		cout << parent[i].getName() << setw(16) << "";
	for (int j = 0; j<vect_size; j++)
		cout << content[j] << setw(16) << "";
	cout << endl;
}

/*
Print all data for each item in the current Directory.
Used for the "ls -l" command.
*/
void Directory::longPrint()
{
	//std::time_t const now_c = std::time(NULL);
	int vect_size = this->vectSize();
	//cout << numFiles << " " << parent[0].owner << endl;
	for (int i = 0; i<numFiles; i++)
	{
		cout << "d";
		printPermissions(parent[i].owner);
		printPermissions(parent[i].group);
		printPermissions(parent[i].publc);
		cout << setw(4) << parent[i].numFiles << "\t\t";
		tm * ptm = localtime(&parent[i].result);
		char buffer[32];
		strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);
		cout << buffer;
		//cout << std::put_time(std::localtime(&now_c), "%F %T");
		cout << "\t" << parent[i].getName() << endl;
	}
	for (int j = 0; j<vect_size; j++)
	{
		cout << "-";
		printPermissions(content[j].getOwner());
		printPermissions(content[j].getGroup());
		printPermissions(content[j].getPublc());
		cout << setw(5) << "1\t" << content[j].getSizeF() << "\t" << content[j].result;
		//cout << std::put_time(std::localtime(&now_c), "%F %T");
		cout << "\t" << content[j] << endl;
	}
}

/*
Used to check if a Directory with the name "line" exists in the current
Directory. Returns true if the Directory is found, returns false otherwise.
*/
bool Directory::duplicateCheckDirc(string line)
{
	bool dupe = false;
	for (int i = 0; i < numFiles; i++)
	if (parent[i].getName() == line)
		dupe = true;
	return dupe;
}

/*
Used to check if a File with the name "line" exists in the current
Directory. Returns true if the file is found, returns false otherwise.
*/
bool Directory::duplicateCheckFile(string line)
{
	bool dupe = false;
	int vect_size = content.size();
	for (int i = 0; i < vect_size; i++)
	if (content[i].getName() == line)
		dupe = true;
	return dupe;
}

/*
Finds the Directory in the current Directory with the
name "line" and returns the Directory's index in the
array pointed to by "parent"
*/
int Directory::matchFindDirc(string line)
{
	int index = 0;
	for (int i = 0; i < numFiles; i++)
	if (parent[i].getName() == line)
		index = i;
	return index;
}

/*
Finds the File in the current Directory with the
name "line" and returns the File's index in the
vector "content"
*/
int Directory::matchFindFile(string line)
{
	int index = 0;
	int vect_size = content.size();
	for (int i = 0; i < vect_size; i++)
	if (content[i].getName() == line)
		index = i;
	return index;
}

/*
Recursively prints the Path of the Directory
using the Directory's parent
*/
string Directory::printPath(Directory * D)
{
	string tmp = "";
	if (this != D)
	{
		int i = 0;
		tmp = "Path not Found";
		while (tmp == "Path not Found" && i<this->numFiles)
		{
			tmp = parent[i].printPath(D);
			i++;
		}
		if (this != D && tmp == "Path not Found")
			return "Path not Found";
		else
		{
			if (this->getName() != "\\")
				tmp.insert(0, 1, '\\');
			tmp.insert(0, this->getName());
		}
	}
	else
		return this->getName();
	return tmp;
}

/*
Sets the read/write/execute permissions for a file.
"line" should be three characters long with each character being
between the '0' character and the '7' character.
*/
void Directory::conversion(string line)
{
	owner = binaryConversion(line[0]);
	group = binaryConversion(line[1]);
	publc = binaryConversion(line[2]);
}


