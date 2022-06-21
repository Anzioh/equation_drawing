#pragma once
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "Viewer.h"
#include "Equation.h"`
#include "Variable.h"
#include "atmsp.h"

using namespace std;

class Caculater {

public:
	vector<Equation> equations;
	Viewer viewer;
	vector<Variable> vars;
	int idCounter = 1;

	string addEquation(string hash, string equation);
	string editEquation(string hash, int id, string equation);
	string getLine(string hash, int id, int dpi, double xMin, double xMax, double yMin, double yMax);
	string getAllLine(string hash, int dpi, double xMin, double xMax, double yMin, double yMax);
	void delEquation(string hash, int id);
	string addVar(string hash, string equation);
	string editVar(string hash, int id, string equation);
	string delVar(string hash, int id);
	string apiTest(string hash, string content);

	Equation& getEquationById(int id);
	Variable& getVaribleById(int id);
	Variable& getVaribleByKey(string key);
	Variable& getVaribleByKey(char key);
	void refreshAllVarsValue();
};