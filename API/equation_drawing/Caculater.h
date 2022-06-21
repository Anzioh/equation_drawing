#pragma once
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "Viewer.h"
#include "Equation.h"`
#include "atmsp.h"

using namespace std;

class Caculater {

public:
	vector<Equation> equations;
	Viewer viewer;
	map<char, double> vars;
	int idCounter = 1;

	string addEquation(string hash, string equation);
	string editEquation(string hash, int id, string equation);
	string getLine(string hash, int id, int dpi, double xMin, double xMax, double yMin, double yMax);
	string getAllLine(string hash);
	void delEquation(string hash, int id);
	string setVar(string hash, string name, string equation);
	void delVar(string hash);
	string apiTest(string hash, string content);

	Equation& getEquationById(int id);
};