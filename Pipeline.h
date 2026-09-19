#pragma once
#include <sstream>
#include <vector>
#include "Simulator.h"
#include "Parser.h"

using namespace std;

class Pipeline{
public:
	Pipeline() {};
	Pipeline(string pipeInput);

	void setInput(string input) {
		this->input = input;
	}

private:

	string input;

};