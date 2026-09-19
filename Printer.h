#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Pipeline.h" 

using namespace std;

enum vrstaIspisa {
	konzola,
	noviFajl,
	postojeciFajl,
	pipelineIs
};

class Printer {
public:

	static Printer& getPrinter() {
		static Printer printer;
		return printer;
	}

	void write();

	void setOutput(string output);
	
	void setIspis(vrstaIspisa ispis);

	string getOutput();

	void setFile(string file, vrstaIspisa ispis);

	void startPipe();

	void endPipe();

	string getPrompt() { return prompt; }

	void setPrompt(string prompt) { this->prompt = prompt; }


protected:

	Printer();

private:

	string prompt = "$";

	vrstaIspisa ispis = konzola;

	string output;

	string file;

};