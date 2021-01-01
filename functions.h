#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include "directory.h"

using namespace std;

string fetchCommand(string & command);
bool fetchFlags(string & line);
bool validCHMOD(string line);
bool between0and7(char c);
string binaryConversion(char c);
void printPermissions(string line);

#endif
