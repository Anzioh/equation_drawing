#pragma once
#include <map>;
#include <vector>
#include <string>

using namespace std;

class Equation {

public:
	int id;
	string equ;
	vector<char> vars;
	string lhs;
	string rhs;

	Equation(int id, string equ, vector<char> vars, string lhs, string rhs);

};
