#include <iostream>
#include <string>
#include "Caculater.h"

using namespace std;

int main() {
	Caculater cal;
	string opt, hash;
	while (cin >> opt) {
		cin >> hash;
		if (opt == "getLine") {
			cout << "";
		}
		else if (opt == "apiTest") {
			string content;
			cin >> content;
			cout << cal.apiTest(hash, content);
		}
	}
}
