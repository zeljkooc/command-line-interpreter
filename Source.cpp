#include "Simulator.h"
#include "Printer.h"

using namespace std;

int main() {
	
	Simulator* s = new Simulator();
	Printer& printer = Printer::getPrinter();
	//string prompt = printer.getPrompt();

	while (1) {
		//Cisti se ulazni bafer od proslih komandi
		cin.clear();
		//Vracanje ispisa na default vrednost
		printer.setIspis(konzola);
		//Interpreter je spreman i cita komandu
		cout << printer.getPrompt() << " ";
		Reader* r = new Reader();
		string input = r->readLine();

		//Komanda se obradjuje i izvrsava
		Parser *sParser = new Parser(input);
		bool uspesno = s->runSimulation(*sParser);

		//Prikazuje se njen izlaz ako je uspesno izvrsavanje
		if (uspesno) {
			//Printer& printer = Printer::getPrinter();
			printer.write();
		}
		
	}
	
	delete s;

	return 0;
}