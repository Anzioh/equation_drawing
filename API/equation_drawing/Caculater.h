#pragma once
#include <map>
#include <vector>
#include "Viewer.h"
#include "Equation.h"`

using namespace std;

class Caculater {

public:
	vector<Equation> Equations;

	string getLine(string hash, int id, string equation);
	string getAllLine(string hash);
	void delEquation(string hash, int id);
	void setVarible(string hash, string name, string equation);

};