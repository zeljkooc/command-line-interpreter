#include "Pipeline.h"
#include "Printer.h"
#include <string>

Pipeline::Pipeline(string pipeInput) {

	//Cevovod se deli na odvojene komande
	stringstream ss(pipeInput);
	vector<string> komande;
	string komanda;
	while (getline(ss, komanda, '|')) {
		//Uklanjanje belina ispred i iza komande
		if (!komanda.empty() && komanda[komanda.length()-1] == ' ')
			komanda = komanda.substr(0, komanda.length()-1);
		if (komanda[0] == ' ')
			komanda = komanda.substr(1);
		komande.push_back(komanda);
	}

	Printer& printer = Printer::getPrinter();

	//Naznaka printeru da je u toku cevovod
	printer.startPipe();

	for (int i = 0;i < komande.size();++i) {

		//Ako je doslo do zadnje komande cevovod se prekida i printer sledeci put prosledjuje izlaz dalje
		if (i == komande.size() - 1) {
			printer.endPipe();
		}

		//Izvrsavanje komande 
		Simulator* s = new Simulator();
		Parser* pParser = new Parser(komande[i]);
		//Izlaz prosle komande se prosledjuje na ulaz sledece komande cevovoda, osim ako se ne radi o prvoj komandi
		if(i!=0)
			pParser->setArgument(printer.getOutput());
		s->runSimulation(*pParser);
	}
}