#pragma once
#include <string>
#include <vector>

using namespace std;

class Variable {

public:
	int id;
	double value = 0;
	string equ;
	vector<char> vars;
	string lhs;
	string rhs;

	Variable(int id);
	Variable(int id, double value, string equ, vector<char> vars, string lhs, string rhs);

};