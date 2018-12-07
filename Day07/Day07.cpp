// Day07.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

using std::string;

int main(int argc, char *argv[]) {
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
	}
	else {
		while (std::cin >> l) {
			lines.push_back(l);
		}
	}

	std::map<char, std::vector<char>> reqMap;
	for (const auto& instr : lines) {
		char step = instr[36];
		char reqStep = instr[5];
		reqMap[step].emplace_back(reqStep);
		reqMap.try_emplace(reqStep, std::vector<char>());
	}

	int stepsTotal = reqMap.size();
	int stepsProccesed = 0;
	string answer;
	while (reqMap.size() > 0) {
		auto min = std::min_element(reqMap.begin(), reqMap.end(),
			[](std::pair<char, std::vector<char>> i, std::pair<char, std::vector<char>> j) { return i.second.size() < j.second.size(); });
		stepsProccesed++;
		answer += min->first;
		for (auto &req : reqMap) {
			std::vector<char> &vec = req.second;
			vec.erase(std::remove(vec.begin(), vec.end(), min->first), vec.end());
		}
		reqMap.erase(min->first);
	}

	std::cout << "Order of sleigh steps: " << answer << '\n';
	return 0;
}
