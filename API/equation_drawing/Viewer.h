#pragma once
#include <string>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Viewer {

public:
	string addEquation(string hash, bool isError, string errorMessage, int id, string equation);
	string editEquation(string hash, bool isError, string errorMessage, int id, string srcEquation, string equation);
	string getLine(string hash, vector<double> x, vector<double> y);
	string getAllLine(string hash);
	string addVar(string hash, bool isError, string errorMessage, int id, string equation);
	string editVar(string hash, bool isError, string errorMessage, int id, string srcEquation, string equation);
	string apiTest(string hash, string content);

};