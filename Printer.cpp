#include "Printer.h"
#include "Pipeline.h"

void Printer::write() {

	ifstream postoji(file);
	//Obrada izlaza
	if (ispis==noviFajl) {
		ofstream datCreate(file); 
		datCreate << output;
	}
	else if (ispis==postojeciFajl) {
		ofstream datAppend(file, std::ios::app);
		datAppend << output;
	}

	switch (ispis) {
	case pipelineIs:
		break;
	case konzola:
		if(output!="")
			cout << output << endl;
		break;
	}
}

void Printer::setOutput(string output) {
	this->output = output;
}

string Printer::getOutput() {
	return output;
}

void Printer::setFile(string file, vrstaIspisa ispis) {
	this->file = file;
	this->ispis = ispis;
}

void Printer::setIspis(vrstaIspisa ispis) {
	this->ispis = ispis;
}

void Printer::startPipe() {
	ispis = pipelineIs;
}

void Printer::endPipe() {
	ispis = konzola;
}

Printer::Printer() {

};