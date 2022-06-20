#include "Caculater.h"

vector<char> getVarInFormula(string fml) {
	vector<char> vars;
	for (int i = 0, check = 0; i < fml.length(); i++) {
		if (fml[i] == 's' && fml[i + 1] == 'i' && fml[i + 2] == 'n') {
			i += 2;
			continue;
		}
		if (fml[i] == 'c' && fml[i + 1] == 'o' && fml[i + 2] == 's') {
			i += 2;
			continue;
		}
		if (fml[i] == 't' && fml[i + 1] == 'a' && fml[i + 2] == 'n') {
			i += 2;
			continue;
		}
		if (fml[i] >= 48 && fml[i] <= 57) {
			continue;
		}
		if (fml[i] != 42 &&
			fml[i] != 43 &&
			fml[i] != 45 &&
			fml[i] != 46 &&
			fml[i] != 47 &&
			fml[i] != 61 &&
			fml[i] != 94 &&
			fml[i] != 40 &&
			fml[i] != 41 &&
			fml[i] != 91 &&
			fml[i] != 93 &&
			fml[i] != 123 &&
			fml[i] != 125) {
			for (int j = 0; j < vars.size(); j++) {
				if (fml[i] == vars[j]) {
					check = 1;
					break;
				}
			}
			if (check == 0) {
				vars.push_back(fml[i]);
				check = 0;
			}
		}
	}
	return vars;
}

string Caculater::apiTest(string hash, string content) {
	return this->viewer.apiTest(hash, content);
}

string Caculater::addEquation(string hash, string equation) {
	bool isError = false;
	string errorMessage = "";
	int eqlIndex = equation.find('=');
	if (eqlIndex != 1) {
		isError = true;
		errorMessage = "Varible error";
	}
	string lhs = equation.substr(0, 1);
	string rhs = equation.substr(eqlIndex + 1);
	vector<char> varsInEqu = getVarInFormula(rhs);
	ATMSP<double> parser;
	ATMSB<double> byteCode;
	for (int i = 0; i < varsInEqu.size(); i++) {
		byteCode.var[i] = 1;
	}
	stringstream ss;
	copy(varsInEqu.begin(), varsInEqu.end(), ostream_iterator<char>(ss, ","));
	if (parser.parse(byteCode, rhs, ss.str())) {
		isError = true;
		errorMessage = "Equation format error";
	}
	if (isError) {
		return viewer.addEquation(hash, isError, errorMessage, -1, "");
	}
	else {
		Equation newEqu(this->idCounter++, equation, varsInEqu, lhs, rhs);
		this->equations.push_back(newEqu);
		return viewer.addEquation(hash, isError, errorMessage, newEqu.id, newEqu.equ);
	}
}

string Caculater::getLine(string hash, int id, int dpi, double xMin, double xMax, double yMin, double yMax) {
	vector<double> x;
	vector<double> y;
	ATMSP<double> parser;
	ATMSB<double> byteCode;
	Equation equ = this->getEquationById(id);
	int xyIndex = 0;

	for (int i = 0; i < equ.vars.size(); i++) {
		if (equ.vars[i] == 'x' || equ.vars[i] == 'y') {
			xyIndex = i;
			continue;
		}
		else {
			byteCode.var[i] = this->vars.find(equ.vars[i])->second;
		}
	}
	stringstream ss;
	copy(equ.vars.begin(), equ.vars.end(), ostream_iterator<char>(ss, ","));
	string varStr = ss.str();
	double xT = (xMax - xMin) / (dpi - 1);
	double yT = (yMax - yMin) / (dpi - 1);
	if (equ.lhs == "y") {
		double xV = xMin;
		for (int i = 0; i < dpi; i++, xV += xT) {
			byteCode.var[xyIndex] = xV;
			parser.parse(byteCode, equ.rhs, varStr);
			x.push_back(xV);
			y.push_back(byteCode.run());
		}
	}
	else if (equ.lhs == "x") {
		double yV = yMin;
		for (int i = 0; i < dpi; i++, yV += yT) {
			byteCode.var[xyIndex] = yV;
			parser.parse(byteCode, equ.rhs, varStr);
			x.push_back(byteCode.run());
			y.push_back(yV);
		}
	}
	return viewer.getLine(hash, x, y);
}

Equation Caculater::getEquationById(int id) {
	for (auto& equ : this->equations) {
		if (equ.id == id) {
			return equ;
		}
	}
}