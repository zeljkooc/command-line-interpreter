#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Reader.h"

using namespace std;

class Redirection {
public:

	Redirection(string fileName) : fileName(fileName) {};

	string fileName;

};

class inputRedirection : public Redirection {
public:
	inputRedirection(string fileName) : Redirection(fileName) {}

	string read() {
		Reader* r = new Reader();
		string argument = r->readFile(fileName);
		return argument;
	}

};

class outputRedirection : public Redirection {

	outputRedirection(string fileName) : Redirection(fileName) {}

	void write(string output) {
		ifstream postoji(fileName);

		ofstream dat(fileName);
		dat << output;
	}

};

class doubleOutputRedirection : public Redirection {

	doubleOutputRedirection(string fileName) : Redirection(fileName) {}

	void write(string output) {
		ifstream postoji(fileName);

		ofstream dat(fileName);
		dat << output;
	}

};