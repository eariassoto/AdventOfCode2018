// Day05.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <ctype.h>
#include <limits>
#include <algorithm>
#include <unordered_set>

using std::string;

size_t calculatePolymerUnits(const string &input) {
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
	return polymerStack.size();
}

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

	auto units = calculatePolymerUnits(input);

	std::cout << "Polymer units: " << units << '\n';

	std::unordered_set<char> letters;
	for (const char ch : input) {
		letters.emplace(tolower(ch));
	}

	size_t minPolymerUnits = std::numeric_limits<size_t>::max();
	char optimumLetter = '0';
	for (const char letter : letters) {
		string copyInput{ input };
		copyInput.erase(std::remove_if(copyInput.begin(),
			copyInput.end(),
			[&](unsigned char x) { return x == letter || tolower(x) == letter; }),
			copyInput.end());
		auto units = calculatePolymerUnits(copyInput);
		if (units < minPolymerUnits) {
			minPolymerUnits = units;
			optimumLetter = letter;
		}
	}

	std::cout << "Minimum units found: " << minPolymerUnits << " removing letter: " << optimumLetter << '\n';
	return 0;
}
