#include <iostream>
#include <string>
#include <cstring>
#include "file.h"
#include "functions.h"
using namespace std;

/*
Defines the << operator. Returns the name of the file.
*/
std::ostream& operator<< (std::ostream& out, const File& f)
{
	out << f.name;
	return out;
}

/*
Sets the read/write/execute permissions for a file.
"line" should be three characters long with each character being
between the '0' character and the '7' character.
*/
void File::conversion(string line)
{
	owner = binaryConversion(line[0]);
	group = binaryConversion(line[1]);
	publc = binaryConversion(line[2]);
}
