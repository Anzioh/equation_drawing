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
	string getAllLine(string hash, vector<int> id, vector<vector<double>> x, vector<vector<double>> y);
	string addVar(string hash, bool isError, string errorMessage, int id, string equation);
	string editVar(string hash, bool isError, string errorMessage, int id, string srcEquation, string equation);
	string delVar(string hash, bool isError, string errorMessage);
	string apiTest(string hash, string content);

};