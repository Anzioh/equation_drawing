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
		errorMessage = "Variable error";
	}
	string lhs = equation.substr(0, 1);
	string rhs = equation.substr(eqlIndex + 1);
	vector<char> varsInEqu = getVarInFormula(rhs);
	for (auto& v : varsInEqu) {
		if (!(v == 'x' || v == 'y') && this->getVaribleByKey(v).id == -1) {
			isError = true;
			errorMessage = "Variable does not exist";
			return this->viewer.addEquation(hash, isError, errorMessage, -1, equation);
		}
	}

	ATMSP<double> parser;
	ATMSB<double> byteCode;
	for (int i = 0; i < varsInEqu.size(); i++) {
		byteCode.var[i] = 1;
	}
	stringstream ss;
	std::copy(varsInEqu.begin(), varsInEqu.end(), ostream_iterator<char>(ss, ","));
	if (parser.parse(byteCode, rhs, ss.str())) {
		isError = true;
		errorMessage = "Equation format error";
	}
	if (isError) {
		return viewer.addEquation(hash, isError, errorMessage, -1, equation);
	}
	else {
		Equation newEqu(this->idCounter++, equation, varsInEqu, lhs, rhs);
		this->equations.push_back(newEqu);
		return viewer.addEquation(hash, isError, errorMessage, newEqu.id, newEqu.equ);
	}
}

string Caculater::editEquation(string hash, int id, string equation) {
	Equation& equ = this->getEquationById(id);
	bool isError = false;
	string errorMessage = "";
	int eqlIndex = equation.find('=');
	if (eqlIndex != 1) {
		isError = true;
		errorMessage = "Variable error";
	}
	string lhs = equation.substr(0, 1);
	string rhs = equation.substr(eqlIndex + 1);
	vector<char> varsInEqu = getVarInFormula(rhs);
	for (auto& v : varsInEqu) {
		if (!(v == 'x' || v == 'y') && this->getVaribleByKey(v).id == -1) {
			isError = true;
			errorMessage = "Variable does not exist";
			return this->viewer.editEquation(hash, isError, errorMessage, equ.id, equ.equ, equation);
		}
	}
	ATMSP<double> parser;
	ATMSB<double> byteCode;
	for (int i = 0; i < varsInEqu.size(); i++) {
		byteCode.var[i] = 1;
	}
	stringstream ss;
	std::copy(varsInEqu.begin(), varsInEqu.end(), ostream_iterator<char>(ss, ","));
	if (parser.parse(byteCode, rhs, ss.str())) {
		isError = true;
		errorMessage = "Equation format error";
	}
	if (isError) {
		return viewer.editEquation(hash, isError, errorMessage, equ.id, equ.equ, equation);
	}
	else {
		string srcEqu = equ.equ;
		equ.equ = equation;
		equ.lhs = lhs;
		equ.rhs = rhs;
		equ.vars = varsInEqu;
		return viewer.editEquation(hash, isError, errorMessage, equ.id, srcEqu, equ.equ);
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
			byteCode.var[i] = this->getVaribleByKey(equ.vars[i]).value;
		}
	}
	stringstream ss;
	std::copy(equ.vars.begin(), equ.vars.end(), ostream_iterator<char>(ss, ","));
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

string Caculater::getAllLine(string hash, int dpi, double xMin, double xMax, double yMin, double yMax) {
	vector<int> id;
	vector<vector<double>> x;
	vector<vector<double>> y;
	ATMSP<double> parser;
	for (int i = 0; i < this->equations.size(); i++) {
		id.push_back(this->equations[i].id);
		x.push_back(vector<double>());
		y.push_back(vector<double>());
		ATMSB<double> byteCode;
		int xyIndex = 0;
		for (int j = 0; j < this->equations[i].vars.size(); j++) {
			if (this->equations[i].vars[j] == 'x' || this->equations[i].vars[j] == 'y') {
				xyIndex = j;
				continue;
			}
			else {
				byteCode.var[j] = this->getVaribleByKey(this->equations[i].vars[j]).value;
			}
		}
		stringstream ss;
		std::copy(this->equations[i].vars.begin(), this->equations[i].vars.end(), ostream_iterator<char>(ss, ","));
		string varStr = ss.str();
		double xT = (xMax - xMin) / (dpi - 1);
		double yT = (yMax - yMin) / (dpi - 1);
		if (this->equations[i].lhs == "y") {
			double xV = xMin;
			for (int j = 0; j < dpi; j++, xV += xT) {
				byteCode.var[xyIndex] = xV;
				parser.parse(byteCode, this->equations[i].rhs, varStr);
				x[i].push_back(xV);
				y[i].push_back(byteCode.run());
			}
		}
		else if (this->equations[i].lhs == "x") {
			double yV = yMin;
			for (int j = 0; j < dpi; j++, yV += yT) {
				byteCode.var[xyIndex] = yV;
				parser.parse(byteCode, this->equations[i].rhs, varStr);
				x[i].push_back(byteCode.run());
				y[i].push_back(yV);
			}
		}
	}
	return this->viewer.getAllLine(hash, id, x, y);
}

string Caculater::delEquation(string hash, int id) {
	this->equations.erase(remove_if(this->equations.begin(), this->equations.end(), [id](Equation const& equ) { return equ.id == id; }), this->equations.end());
	return this->viewer.delEquation(hash, false, "");
}

string Caculater::addVar(string hash, string equation) {
	bool isError = false;
	string errorMessage = "";
	int eqlIndex = equation.find('=');
	if (eqlIndex != 1) {
		isError = true;
		errorMessage = "Variable error";
	}
	string lhs = equation.substr(0, 1);
	if (this->getVaribleByKey(lhs).id != -1) {
		isError = true;
		errorMessage = "Variable already exists";
		return this->viewer.addVar(hash, isError, errorMessage, -1, equation);
	}
	string rhs = equation.substr(eqlIndex + 1);
	vector<char> varsInEqu = getVarInFormula(rhs);
	for (auto& v : varsInEqu) {
		if (v == lhs.c_str()[0]) {
			isError = true;
			errorMessage = "Loop definition Variable";
			return this->viewer.addVar(hash, isError, errorMessage, -1, equation);
		}
		else if (this->getVaribleByKey(v).id == -1) {
			isError = true;
			errorMessage = "Variable does not exist";
			return this->viewer.addVar(hash, isError, errorMessage, -1, equation);
		}
		for (auto& vE : this->getVaribleByKey(v).vars) {
			if (vE == lhs.c_str()[0]) {
				isError = true;
				errorMessage = "Loop definition Variable";
				return this->viewer.addVar(hash, isError, errorMessage, -1, equation);
			}
		}
	}
	ATMSP<double> parser;
	ATMSB<double> byteCode;
	for (int i = 0; i < varsInEqu.size(); i++) {
		byteCode.var[i] = this->getVaribleByKey(varsInEqu[i]).value;
	}
	stringstream ss;
	std::copy(varsInEqu.begin(), varsInEqu.end(), ostream_iterator<char>(ss, ","));
	if (parser.parse(byteCode, rhs, ss.str())) {
		isError = true;
		errorMessage = "Equation format error";
		return viewer.addVar(hash, isError, errorMessage, -1, equation);
	}
	Variable newVar(this->idCounter++, byteCode.run(), equation, varsInEqu, lhs, rhs);
	this->vars.push_back(newVar);
	return viewer.addVar(hash, isError, errorMessage, newVar.id, newVar.equ);
}

string Caculater::editVar(string hash, int id, string equation) {
	Variable& var = this->getVaribleById(id);
	bool isError = false;
	string errorMessage = "";
	int eqlIndex = equation.find('=');
	if (eqlIndex != 1) {
		isError = true;
		errorMessage = "Variable error";
	}
	string lhs = equation.substr(0, 1);
	if (lhs != var.lhs && this->getVaribleByKey(lhs).id != -1) {
		isError = true;
		errorMessage = "Variable already exists";
		return this->viewer.editVar(hash, isError, errorMessage, var.id, var.equ, equation);
	}
	string rhs = equation.substr(eqlIndex + 1);
	vector<char> varsInEqu = getVarInFormula(rhs);
	for (auto& v : varsInEqu) {
		if (v == lhs.c_str()[0]) {
			isError = true;
			errorMessage = "Loop definition Variable";
			return this->viewer.editVar(hash, isError, errorMessage, var.id, var.equ, equation);
		}
		else if (this->getVaribleByKey(v).id == -1) {
			isError = true;
			errorMessage = "Variable does not exist";
			return this->viewer.editVar(hash, isError, errorMessage, var.id, var.equ, equation);
		}
		for (auto& vE : this->getVaribleByKey(v).vars) {
			if (vE == lhs.c_str()[0]) {
				isError = true;
				errorMessage = "Loop definition Variable";
				return this->viewer.editVar(hash, isError, errorMessage, var.id, var.equ, equation);
			}
		}
	}
	ATMSP<double> parser;
	ATMSB<double> byteCode;
	for (int i = 0; i < varsInEqu.size(); i++) {
		byteCode.var[i] = this->getVaribleByKey(varsInEqu[i]).value;
	}
	stringstream ss;
	std::copy(varsInEqu.begin(), varsInEqu.end(), ostream_iterator<char>(ss, ","));
	if (parser.parse(byteCode, rhs, ss.str())) {
		isError = true;
		errorMessage = "Equation format error";
		return viewer.editVar(hash, isError, errorMessage, var.id, var.equ, equation);
	}
	string srcEqu = var.equ;
	var.equ = equation;
	var.lhs = lhs;
	var.rhs = rhs;
	var.vars = varsInEqu;
	var.value = byteCode.run();
	this->refreshAllVarsValue();
	return viewer.editVar(hash, isError, errorMessage, var.id, srcEqu, var.equ);
}

string Caculater::delVar(string hash, int id) {
	Variable var = this->getVaribleById(id);
	for (auto& equ : this->equations) {
		if (find(equ.vars.begin(), equ.vars.end(), var.lhs.c_str()[0]) != equ.vars.end()) {
			return this->viewer.delVar(hash, true, "Variable is being used");
		}
	}
	this->vars.erase(remove_if(this->vars.begin(), this->vars.end(), [id](Variable const& v) { return v.id == id; }), this->vars.end());
	return this->viewer.delVar(hash, false, "");
}

Equation& Caculater::getEquationById(int id) {
	for (auto& equ : this->equations) {
		if (equ.id == id) {
			return equ;
		}
	}
}

Variable& Caculater::getVaribleById(int id) {
	for (auto& v : this->vars) {
		if (v.id == id) {
			return v;
		}
	}
}

Variable& Caculater::getVaribleByKey(string key) {
	for (auto& v : this->vars) {
		if (v.lhs == key) {
			return v;
		}
	}
	Variable var(-1);
	return var;
}

Variable& Caculater::getVaribleByKey(char key) {
	for (auto& v : this->vars) {
		if (v.lhs.c_str()[0] == key) {
			return v;
		}
	}
	Variable var(-1);
	return var;
}

void Caculater::refreshAllVarsValue() {
	for (auto& v : this->vars) {
		ATMSP<double> parser;
		ATMSB<double> byteCode;
		for (int i = 0; i < v.vars.size(); i++) {
			byteCode.var[i] = this->getVaribleByKey(v.vars[i]).value;
		}
		stringstream ss;
		std::copy(v.vars.begin(), v.vars.end(), ostream_iterator<char>(ss, ","));
		parser.parse(byteCode, v.rhs, ss.str());
		v.value = byteCode.run();
	}
}

