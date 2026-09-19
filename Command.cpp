#include "Command.h"
#include "Simulator.h"
#include "Printer.h"

#include <sstream>
#include <iostream>
#include <cstdio> 
#include <fstream>

using namespace std;

void Command::setArguments(vector<string> arguments) {
	this->arguments = arguments;
}

string Wc::executeCommand() {

	Reader* fr = new Reader();
	//arguments[0] = fr->readFile(arguments[0]);
	
	int charCounter = 0;
	while (arguments[0][charCounter] != '\0') {
		if (isspace(arguments[0][charCounter++]))
			wordsCounter++;
	}
	if(!isspace(arguments[0][arguments[0].length()-1]))
		wordsCounter++;

	if (opt == "c")
		return to_string(charCounter);
	else
		return to_string(wordsCounter);
}

string Echo::executeCommand() {

	output = arguments[0];
	return arguments[0];
}

string Touch::executeCommand() {

	ifstream postoji(arguments[0]);
	if (postoji)
		return "Greska! Fajl vec postoji!";

	ofstream dat(arguments[0]);

	return "";
}

string Time::executeCommand() {

	std::time_t now = std::time(0);

	std::tm localTime;
	localtime_s(&localTime, &now);

	string output = to_string(localTime.tm_hour) + ":" + to_string(localTime.tm_min) + ":" + to_string(localTime.tm_sec);

	return output;
}

string Date::executeCommand() {

	std::time_t now = std::time(0);

	std::tm localTime;
	localtime_s(&localTime, &now);

	string output = to_string(localTime.tm_mday) + "." + to_string(localTime.tm_mon + 1) + "." + to_string(localTime.tm_year + 1900) + ".";

	return output;
}

string Prompt::executeCommand() {

	Printer& printer = Printer::getPrinter();
	printer.setPrompt(arguments[0]);
	return "";
}

string Rm::executeCommand() {

	ifstream postoji(arguments[0]);
	if (!postoji)
		return "Greska! Fajl ne postoji!";
	postoji.close();
	remove(arguments[0].c_str());
	return "";
}

string Truncate::executeCommand() {

	ofstream(arguments[0],std::ios::trunc);
	return "";
}

string Tr::executeCommand() {

	string text = arguments[0];
	string what = arguments[1];
	string with = arguments.size()==3 ? arguments[2] : "";
	
	if (what=="") return text;

	size_t startPos = 0;
	while ((startPos = text.find(what, startPos)) != std::string::npos) {
		text.replace(startPos, what.length(), with);
		startPos += with.length();
	}
	return text;
}

string Head::executeCommand() {

	int count = stoi(opt.substr(1));
	string output = "";
	for (char c : arguments[0]) {
		if (c == '\n')
			count--;
		if (count == 0)
			break;
		output += c;
	}
	return output;
}

string Batch::executeCommand() {

	Simulator* s = new Simulator();
	string line;
	istringstream stream(arguments[0]);

	while (getline(stream, line)) {
		//Komanda se obradjuje i izvrsava
		Parser* sParser = new Parser(line);
		bool uspesno = s->runSimulation(*sParser);

		//Prikazuje se njen izlaz ako je uspesno izvrsavanje
		if (uspesno) {
			Printer& printer = Printer::getPrinter();
			printer.write();
		}

	}
	return "";
}
