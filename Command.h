#pragma once
#include <string>
#include <fstream>
#include <ctime>
#include "Reader.h"
#include <vector>

using namespace std;

class Command {
public:

	void setArguments(vector<string> arguments);

	virtual string executeCommand()=0;

protected:


	Command(vector<string> arguments) : arguments(arguments) {};

	Command(string opt, vector<string> arguments) : opt(opt),arguments(arguments) {};

	Command() {};

	~Command() {};

	string opt="";

	vector<string> arguments;

	string output = "";

	string fileName = "";

};

class Wc : public Command {
public:

	Wc(vector<string> arguments, string opt) : Command(opt, arguments) {};

	virtual string executeCommand() override;

private:

	int wordsCounter = 0;

	int charCounter = 0;

};

class Echo : public Command {
public:

	Echo(vector<string> arguments) : Command(arguments){}

	virtual string executeCommand() override;
};

class Touch : public Command {
public:

	Touch(vector<string> arguments) : Command(arguments){};

	virtual string executeCommand() override;
};

class Time : public Command {
public:

	Time() : Command() {};

	virtual string executeCommand() override;
};

class Date : public Command {
public:

	Date() : Command() {};
	 
	virtual string executeCommand() override;
};

class Prompt : public Command {
public:

	Prompt(vector<string> arguments) : Command(arguments) {};

	virtual string executeCommand() override;
};

class Rm : public Command {
public:

	Rm(vector<string> arguments) : Command(arguments) {};

	virtual string executeCommand() override;
};

class Truncate: public Command {
public:

	Truncate(vector<string> arguments) : Command(arguments) {};

	virtual string executeCommand() override;
};

class Tr : public Command {
public:

	Tr(vector<string> arguments) : Command(arguments)  {};

	virtual string executeCommand() override;
};

class Head : public Command {
public:

	Head(vector<string> arguments, string opt) : Command(opt, arguments) {};

	virtual string executeCommand() override;
};

class Batch : public Command {
public:

	Batch(vector<string> arguments) : Command(arguments) {};

	virtual string executeCommand() override;
};