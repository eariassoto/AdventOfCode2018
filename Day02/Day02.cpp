// Day02.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::string;
typedef std::unordered_map<char, int>::value_type hashMapValueType;

int main()
{
	std::vector<string> lines;
	string l;

	while (std::cin >> l) {
		lines.push_back(l);
	}

	int boxesWith2Repeated = 0;
	int boxesWith3Repeated = 0;

	std::unordered_map<char, int> charCount;
	for (const string &line : lines) {
		charCount.clear();
		for (const char ch : line) {
			charCount[ch] += 1;
		}

		auto it = find_if(charCount.begin(), charCount.end(),
			[](const hashMapValueType& vt) { return vt.second == 2; }
		);
		if (it != charCount.end()) {
			boxesWith2Repeated++;
		}

		it = find_if(charCount.begin(), charCount.end(),
			[](const hashMapValueType& vt) { return vt.second == 3; }
		);
		if (it != charCount.end()) {
			boxesWith3Repeated++;
		}
	}

	int checksum = boxesWith2Repeated * boxesWith3Repeated;
	std::cout << "The checksum for the list is: " << checksum << '\n';

	return 0;
}
