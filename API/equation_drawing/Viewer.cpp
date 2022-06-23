#include "Viewer.h"

string Viewer::addEquation(string hash, bool isError, string errorMessage, int id, string equation) {
	json response = {
		{"id", id},
		{"equation", equation},
		{"isError", isError},
		{"errorMessage", errorMessage},
		{"hash", hash}
	};
	return response.dump();
}

string Viewer::editEquation(string hash, bool isError, string errorMessage, int id, string srcEquation, string equation) {
	json response = {
		{"id", id},
		{"srcEquation", srcEquation},
		{"equation", equation},
		{"isError", isError},
		{"errorMessage", errorMessage},
		{"hash", hash}
	};
	return response.dump();
}

string Viewer::delEquation(string hash, bool isError, string errorMessage) {
	json response = {
		{"isError", isError},
		{"errorMessage", errorMessage},
		{"hash", hash}
	};
	return response.dump();
}

string Viewer::getLine(string hash, vector<double> x, vector<double> y) {
	json response = {
		{"x", x},
		{"y", y},
		{"hash", hash}
	};
	return response.dump();
}

string Viewer::getAllLine(string hash, vector<int> id, vector<vector<double>> x, vector<vector<double>> y) {
	json response = {
		{"hash", hash}
	};
	response["equations"] = json::array();
	for (int i = 0; i < id.size(); i++) {
		json equ = json::object({
			{"id", id[i]},
			{"x", x[i]},
			{"y", y[i]}
			});
		response["equations"].push_back(equ);
	}
	return response.dump();
}

string Viewer::addVar(string hash, bool isError, string errorMessage, int id, string equation) {
	json response = {
		{"id", id},
		{"equation", equation},
		{"isError", isError},
		{"errorMessage", errorMessage},
		{"hash", hash}
	};
	return response.dump();
}

string Viewer::editVar(string hash, bool isError, string errorMessage, int id, string srcEquation, string equation) {
	json response = {
		{"id", id},
		{"srcEquation", srcEquation},
		{"equation", equation},
		{"isError", isError},
		{"errorMessage", errorMessage},
		{"hash", hash}
	};
	return response.dump();
}

string Viewer::delVar(string hash, bool isError, string errorMessage) {
	json response = {
		{"isError", isError},
		{"errorMessage", errorMessage},
		{"hash", hash}
	};
	return response.dump();
}

string Viewer::apiTest(string hash, string content) {
	json response = {
		{"content", content},
		{"hash", hash}
	};
	return response.dump();
}
