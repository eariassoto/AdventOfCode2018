// Day05.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <ctype.h>

using std::string;

int main(int argc, char *argv[]) {
	string input;

	if (argc == 2) {
		std::ifstream inputFile{ argv[1] };
		if (!inputFile.is_open()) {
			std::cout << "Could not open input file\n";
			return 0;
		}
		std::getline(inputFile, input);
	}
	else {
		std::cin >> input;
	}

	std::stack<char> polymerStack;

	for (const char ch : input) {
		if (polymerStack.empty()) {
			polymerStack.push(ch);
			continue;
		}
		char top = polymerStack.top();
		if (top != ch && (tolower(top) == ch || tolower(ch) == top)) {
			polymerStack.pop();
		}
		else {
			polymerStack.push(ch);
		}
	}

	std::cout << "Polymer units: " << polymerStack.size() << '\n';
	return 0;
}
