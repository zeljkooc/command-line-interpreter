#include "Parser.h"
#include "Redirection.h"
#include "Printer.h"
#include "Pipeline.h"
#include "ErrorHandler.h"
#include <vector>
#include <string>


Parser::Parser(string input) : input(input) {}

string Parser::getCommand() { return command; }

string Parser::getOpt() { return opt; }

vector<string> Parser::getArguments() { return arguments; }

void Parser::setArgument(string argument) { arguments.push_back(argument); }

string Parser::getFile() { return fileName; }

int Parser::parseInput() {
	//Provera da li su komande u cevovodu
	for(char c : input)
		if (c == '|') {
			Pipeline *p = new Pipeline(input);
			return 1;
		}

	//Razdvajanje inputa na reci koje se kasnije parsiraju 
	vector<string> words;
	string word;
	bool openedQuot = false;
	bool redirectFlag=false;
	for (char c : input) {
		if (c == '>' || c == '<') {
			if(!openedQuot)
				redirectFlag = true;
			break;
		}
		if (c == ' ' || c == '\t') {
			if (!word.empty()) {
				words.push_back(word);
				word.clear();
			}
		}
		else
			word += c;
		if (c == '"')
			openedQuot = !openedQuot;
	}
	words.push_back(word);

	//Provera sintaksu komande
	ErrorHandler* eh = new ErrorHandler();
	if (eh->checkErrors(input))
		return 0;

	//Komanda je prva rec
	command = words[0];

	//Uzima se instanca printera za prebacivanje izlaza
	Printer& printer = Printer::getPrinter();

	openedQuot = false;
	//Prolazimo kroz reci komande koje su podeljene belinama
	for (int i = 1;i < words.size();++i) {
		//Obelezavamo pocetak teksta
		if (words[i][0] == '"')
			openedQuot = true;
		//Ako vidimo rec koja pocinje sa "-" to je opcija
		else if (!openedQuot && words[i][0] == '-')
			opt = words[i].substr(1);
		//Ako u komandi postoji fajl on se prosledjuje dalje
		else if (!openedQuot && !redirectFlag) {
			Reader* r = new Reader();
			if (words[i] != "" && command != "touch" && command != "rm" && command != "truncate") {
				arguments.push_back(r->readFile(words[i]));
				if (arguments[0] == "")
					return -1;
			}
			fileName = words[i];
		}
	}

	if (redirectFlag) {

		//Dohvatanje fajlova za redirekciju
		stringstream ss(input);
		string connectedInput = "";
		while (getline(ss, word, ' ')) {
			connectedInput += word;
		}

		size_t startPos = 0;
		size_t endPos = 0;

		bool inputFlag = false;
		bool outputFlag = false;

		//Odredjivanje pocetnog indeksa za input i output redirection
		if ((startPos = connectedInput.find('<')) != std::string::npos)
			inputFlag = true;
		if ((endPos = connectedInput.find('>')) != std::string::npos)
			outputFlag = true;

		//Razliciti nacini za izvlacenje naziva fajla iz stringa u odnosu na sadrzaj komande
		if (inputFlag && outputFlag) {
			inputRedirection* inpRed = new inputRedirection(connectedInput.substr(startPos + 1, endPos - startPos - 1));
			arguments.push_back(inpRed->read());
			if (arguments[0] == "")
				return -1;
		}

		if (inputFlag && !outputFlag) {
			inputRedirection* inpRed = new inputRedirection(connectedInput.substr(startPos + 1));
			arguments.push_back(inpRed->read());
			if (arguments[0] == "")
				return -1;
		}

		if (outputFlag) {
			if (connectedInput[endPos + 1] == '>')
				printer.setFile(connectedInput.substr(endPos + 2), postojeciFajl);
			else
				printer.setFile(connectedInput.substr(endPos + 1), noviFajl);
		}
	}

	//Dohvtanje argumenta pod navodnicima
	string argument = "";
	if (!openedQuot) return 0;

	bool write = false;
	for (char c : input) {
		if (write && c != '"')
			argument += c;
		if (c == '"') {
			if (write) {
				arguments.push_back(argument);
				argument = "";
			}
			write = !write;
		}
	}

	return 0;
}