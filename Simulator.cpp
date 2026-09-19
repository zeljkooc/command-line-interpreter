#include "Simulator.h"
#include "Redirection.h"
#include "Printer.h"
#include <vector>

Simulator::Simulator() {};

bool Simulator::runSimulation(Parser &sParser) {

	int flag = sParser.parseInput();

	//Ako je parser u cevovodu ili ima neku gresku prekida se izvrsavanje komande
		//Cevovod: 1
		//Nastavlja se izvrsavanje: 0
		//Greska: -1
	if(flag == 1)
		return true;
	if (flag == -1)
		return false;

	//Delovi parsera se izdvajaju
	string command = sParser.getCommand();
	vector<string> arguments = sParser.getArguments();
	string opt = sParser.getOpt();
	string fileName = sParser.getFile();

	int trebaArgument=0;

	//Kreira se objekat odredjene komande
	Command* komanda = chooseCommand(command, arguments, opt, fileName,&trebaArgument,flag);
	if (!komanda)
		return false;

	//Ako je potreban argument i nije unet u prvoj liniji
	if ((trebaArgument == 1 && arguments.size() == 0)) {
		//On se unosi u sledecim redovima dok ne dodje do EOF
		arguments.push_back(sRead->readParagraph());
		komanda->setArguments(arguments);
	}
	//Posebno se unosi za komandu tr jer ona svakako vec ima jedan argument
	if ((trebaArgument == 1 && command == "tr" && arguments.size() == 1)) {
		arguments.insert(arguments.begin(),sRead->readParagraph());
		komanda->setArguments(arguments);
	}
	
	//Izlaz komande se prosledjuje printeru na dalju obradu
	string output = komanda->executeCommand();
	Printer& printer = Printer::getPrinter();
	printer.setOutput(output);

	return true;
}

Command* Simulator::chooseCommand(string command, vector<string> arguments, string opt, string fileName,int *trebaArgument,int flag) {
	Command* komanda = nullptr;
	if (command == "wc") {
		komanda = new Wc(arguments, opt);
		*trebaArgument = 1;
	}
	else if (command == "echo") {
		komanda = new Echo(arguments);
		*trebaArgument = 1;
	}
	else if (command == "touch") {
		arguments.push_back(fileName);
		komanda = new Touch(arguments);
	}
	else if (command == "truncate") {
		arguments.push_back(fileName);
		komanda = new Truncate(arguments);
	}
	else if (command == "time")
		komanda = new Time();
	else if (command == "date")
		komanda = new Date();
	else if (command == "prompt")
		komanda = new Prompt(arguments);
	else if (command == "rm") {
		arguments.push_back(fileName);
		komanda = new Rm(arguments);
	}
	else if (command == "tr") {
		komanda = new Tr(arguments);
		*trebaArgument = 1;
	}
	else if (command == "head") {
		komanda = new Head(arguments,opt);
		*trebaArgument = 1;
	}
	else if (command == "batch") {
		komanda = new Batch(arguments);
		*trebaArgument = 1;
	}
	else {
		cout << "Unknown command: " << command << endl;
		return nullptr;
	}
	return komanda;
}