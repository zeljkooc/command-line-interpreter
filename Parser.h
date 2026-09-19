#pragma once
#include <string>
#include <sstream>
#include <vector>
#include "Reader.h"

using namespace std;

class Parser {
private:

	string input;

	string command;

	string opt;

	vector<string> arguments;

	string fileName="";
	
public:
	Parser(string input);

	string getCommand();

	string getOpt();

	vector<string> getArguments();

	void setArgument(string argument);

	string getFile();

	int parseInput();

};