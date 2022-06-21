#pragma once
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "Viewer.h"
#include "Equation.h"`
#include "Varible.h"
#include "atmsp.h"

using namespace std;

class Caculater {

public:
	vector<Equation> equations;
	Viewer viewer;
	vector<Varible> vars;
	int idCounter = 1;

	string addEquation(string hash, string equation);
	string editEquation(string hash, int id, string equation);
	string getLine(string hash, int id, int dpi, double xMin, double xMax, double yMin, double yMax);
	string getAllLine(string hash);
	void delEquation(string hash, int id);
	string addVar(string hash, string equation);
	string editVar(string hash, int id, string equation);
	void delVar(string hash);
	string apiTest(string hash, string content);

	Equation& getEquationById(int id);
	Varible& getVaribleById(int id);
	Varible& getVaribleByKey(string key);
	Varible& getVaribleByKey(char key);
	void refreshAllVarsValue();
};