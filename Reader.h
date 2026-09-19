#pragma once
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Reader {
private:

	string input;

public:

	Reader();

	string readParagraph();

	string readLine();

	string readFile(string datName);

};
