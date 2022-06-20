#include "Equation.h"

Equation::Equation(int id, string equ, vector<char> vars, string lhs, string rhs) {
	this->id = id;
	this->equ = equ;
	this->vars = vars;
	this->lhs = lhs;
	this->rhs = rhs;
}