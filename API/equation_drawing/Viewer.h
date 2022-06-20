#pragma once
#include <string>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Viewer {

public:
	string addEquation(string hash, bool isError, string errorMessage, int id, string equation);
	string editEquation();
	string getLine(string hash, vector<double> x, vector<double> y);
	string getAllLine(string hash);
	string apiTest(string hash, string content);

};