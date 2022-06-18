#include "Viewer.h"

string Viewer::apiTest(string hash, string content) {
	json response = {
		{"content", content},
		{"hash", hash}
	};
	return response.dump();
}
