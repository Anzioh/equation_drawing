#pragma once
#include <map>;
#include <vector>
#include <string>

using namespace std;

class Equation {
	
public:
	int Id;
	string Formula;
	vector<double> X;
	vector<double> Y;

	static map<string, double> Variables;
	static int IdCounter;

};
