#include "Varible.h"

Varible::Varible(int id) {
	this->id = id;
}

Varible::Varible(int id, double value, string equ, vector<char> vars, string lhs, string rhs) {
	this->id = id;
	this->value = value;
	this->equ = equ;
	this->vars = vars;
	this->lhs = lhs;
	this->rhs = rhs;
}
