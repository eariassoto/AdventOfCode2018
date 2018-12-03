// Day02.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>

using std::string;
typedef std::unordered_map<char, int>::value_type hashMapValueType;

int main(int argc, char *argv[])
{
	std::vector<string> lines;
	string l;

	if (argc == 2) {
		std::ifstream inputFile{ argv[1] };
		if (!inputFile.is_open()) {
			std::cout << "Could not open input file\n";
			return 0;
		}
		string str;
		while (std::getline(inputFile, str)) {
			// Line contains string of length > 0 then save it in vector
			if (str.size() > 0)
				lines.push_back(str);
		}
	} else {
		while (std::cin >> l) {
			lines.push_back(l);
		}
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

	bool found = false;
	string r1, r2;
	for (int i = 0; !found && i < lines.size(); i++) {
		string &tmp = lines[i];
		for (int j = i + 1; !found && j < lines.size(); j++) {
			int dif = 0;
			string &tmp2 = lines[j];
			for (int k = 0; k < tmp2.size(); k++) {
				if (tmp[k] != tmp2[k]) {
					dif++;
				}
			}
			if (dif == 1) {
				found = true;
				r1 = tmp;
				r2 = tmp2;
			}
		}
	}

	if (found) {
		string answer;
		for (int i = 0; i < r1.size(); i++) {
			if (r1[i] == r2[i]) {
				answer += r1[i];
			}
		}
		std::cout << "The common letters for the boxes are: " << answer << '\n';
	}

	return 0;
}
