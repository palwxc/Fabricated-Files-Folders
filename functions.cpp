#include <iostream>
#include "functions.h"

using namespace std;

/*
Removes first word from "command" and returns it as a string.
Updates "command" via pass by reference, removing first word
and the character after the first word.
*/
string fetchCommand(string & command)
{
	int stringSize = command.size();
	string tmp = "";
	string firstWord = "";

	//puts first word of "command" in "firstWord"
	while (stringSize > 0 && command[0] != '\n' && command[0] != ' ')
	{
		tmp = command[0];
		firstWord.append(tmp);
		command.erase(0, 1);
		stringSize = command.size();
	}

	//removes the first character in "command"
	command.erase(0, 1);
	return firstWord;
}

/*
Returns false if the first character of "line" is not a "-".
Otherwise, returns true and removes spaces and new line characters
up to the next character that is not a space or a new line character
*/
bool fetchFlags(string & line)
{
	bool flag = false;
	if (line[0] == '-')
	{
		int i = 0;
		int lineSize = line.size();
		while (i < lineSize && line[i] != '\n' && line[i] != ' ')
		{
			line.erase(0, 1);
			i++;
		}
		flag = true;
		return flag;
	}
	return flag;
}
/*
Returns true if every character in "line" is a character between
"0" and "7" (inclusively) and if line is three characters long.
Otherwise, returns false. Only used in "runCommand"
*/
bool validCHMOD(string line)
{
	bool valid = false;
	int length = line.size();
	if (length == 3)
	if (between0and7(line[0]) && between0and7(line[1]) && between0and7(line[2]))
		valid = true;
	return valid;
}

/*
Returns true if "c" is between the ascii values of 48 and 55
(corresponding to the characters for 0 to 7). Otherwise,
returns false. Only used in "validCHMOD"
*/
bool between0and7(char c)
{
	bool valid = false;
	if (c >= 48 && c <= 55)
		valid = true;
	return valid;
}

/*
Returns the inputted character (should be 0 to 7) in binary
as a string (000 to 111). If character is not between 1 and 7
then return "000". Used in the "conversion" member functions
for the file and directory classes.
*/
string binaryConversion(char c)
{
	if (c == '7')
		return "111";
	if (c == '6')
		return "110";
	if (c == '5')
		return "101";
	if (c == '4')
		return "100";
	if (c == '3')
		return "011";
	if (c == '2')
		return "010";
	if (c == '1')
		return "001";
	return "000";
}

/*
Used for printing read/write/execute permissions with cout.
Checks if first three characters are '1' and prints
corresponding character if so. Only used in longPrint.
*/
void printPermissions(string line)
{
	if (line[0] == '1')
		cout << 'r';
	else
		cout << '-';
	if (line[1] == '1')
		cout << 'w';
	else
		cout << '-';
	if (line[2] == '1')
		cout << 'x';
	else
		cout << '-';
}
