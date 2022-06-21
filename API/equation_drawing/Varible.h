#pragma once
#include <string>
#include <vector>

using namespace std;

class Varible {

public:
	int id;
	double value = 0;
	string equ;
	vector<char> vars;
	string lhs;
	string rhs;

	Varible(int id);
	Varible(int id, double value, string equ, vector<char> vars, string lhs, string rhs);

};