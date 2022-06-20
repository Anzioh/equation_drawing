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

string Viewer::apiTest(string hash, string content) {
	json response = {
		{"content", content},
		{"hash", hash}
	};
	return response.dump();
}
