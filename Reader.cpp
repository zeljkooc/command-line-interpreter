#include "Reader.h"

Reader::Reader() {};

string Reader::readParagraph() {
	string inp="";
	int c;
	while ((c=cin.get()) != EOF) {
		inp += static_cast<char>(c);
	}
	return inp;
}

string Reader::readLine() {
	getline(cin, input);
	return input;
}

string Reader::readFile(string datName) {
	ifstream dat(datName);
	if (datName == "")
		return "";
	if (!dat) {
		cout << "Greska!\n";
		return "";
	}

	string row;
	string output = "";
	while (getline(dat, row)) {
		output += row+"\n";
	}
	output = output.substr(0,output.size()-1);
	return output;
}

