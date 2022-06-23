#include <iostream>
#include <string>
#include "Caculater.h"

using namespace std;

int main() {
	Caculater cal;
	string opt, hash;
	while (cin >> opt) {
		cin >> hash;
		if (opt == "getLine") {
			int id, dpi;
			double xMin, xMax, yMin, yMax;
			cin >> id >> dpi >> xMin >> xMax >> yMin >> yMax;
			cout << cal.getLine(hash, id, dpi, xMin, xMax, yMin, yMax);
		}
		else if (opt == "getAllLine") {
			int  dpi;
			double xMin, xMax, yMin, yMax;
			cin >> dpi >> xMin >> xMax >> yMin >> yMax;
			cout << cal.getAllLine(hash, dpi, xMin, xMax, yMin, yMax);
		}
		else if (opt == "addEquation") {
			string equation;
			cin >> equation;
			cout << cal.addEquation(hash, equation);
		}
		else if (opt == "editEquation") {
			int id;
			string equation;
			cin >> id >> equation;
			cout << cal.editEquation(hash, id, equation);
		}
		else if (opt == "delEquation") {
			int id;
			cin >> id;
			cout << cal.delEquation(hash, id);
		}
		else if (opt == "addVar") {
			string equation;
			cin >> equation;
			cout << cal.addVar(hash, equation);
		}
		else if (opt == "editVar") {
			int id;
			string equation;
			cin >> id >> equation;
			cout << cal.editVar(hash, id, equation);
		}
		else if (opt == "delVar") {
			int id;
			cin >> id;
			cout << cal.delVar(hash, id);
		}
		else if (opt == "apiTest") {
			string content;
			cin >> content;
			cout << cal.apiTest(hash, content);
		}
	}
}
