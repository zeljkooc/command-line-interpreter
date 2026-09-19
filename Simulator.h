#pragma once
#include "Reader.h"
#include "Parser.h"
#include "Command.h"

#include <iostream>

using namespace std;

class Simulator {
public:

	Simulator();

	bool runSimulation(Parser &sParser);

private:

	Command* chooseCommand(string command, vector<string> arguments, string opt, string fileName, int* trebaArgument,int flag);

	Reader* sRead = new Reader();
	Parser* sParser= nullptr;
};