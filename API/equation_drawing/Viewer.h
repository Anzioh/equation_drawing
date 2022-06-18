#pragma once
#include <string>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Viewer {

public:
	string getLine(string hash);
	string apiTest(string hash, string content);

};