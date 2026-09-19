#pragma once
#include <vector>
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

class ErrorHandler {

public:
	ErrorHandler() {}
	//Proverava da li ima neocekivanih simbola
	bool checkErrors(string input) {

		bool openedQuot = false;

		string errorSymbols;
		errorSymbols.resize(600);

		int duzina = 0;
		bool error = false;

		for (char c : input) {
			if (!openedQuot && !isalnum(c) && c != '-' && c!=' ' && c!='"' && c!='.' && c!='>' && c!='<') {
				errorSymbols[duzina] = '^';
				error = true;
			}
			else
				errorSymbols[duzina] = ' ';

			if (c == '"')
				openedQuot = !openedQuot;

			++duzina;
		}
		if (error) {
			cout << "\nError - unexpected characters:\n";
			cout << input << endl;
			for (int i = 0;i < duzina;++i) {
				cout << errorSymbols[i];
			}
			cout << endl;
		}
		
		return error;
	}
};