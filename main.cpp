//Programmer: Phillip LaFrance	//Student ID: 12398940
//Instructor: Josh Wilkerson	//Section: B		//Date: 09/08/2019

#include <iostream>
#include <string>
#include <cstring>

#include "directory.h"
#include "file.h"
#include "functions.h"

using namespace std;

int main()
{
	srand(time(NULL));
	string commandFirstWord, command = "";
	Directory root;
	Directory * D = &root;

	do
	{
		cout << "C:" << root.printPath(D) << ":~$ ";
		getline(cin, command);

		//places first word of command in its own string
		commandFirstWord = fetchCommand(command);

		if (commandFirstWord != "pwd")
			D = &D->runCommand(commandFirstWord, command);
		else
			cout << root.printPath(D) << endl;
		command = "";
	} while (commandFirstWord != "exit" && commandFirstWord != "quit");

	return 0;
}
