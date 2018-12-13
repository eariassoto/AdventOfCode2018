// Day07.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

using std::string;
using StepsMap = std::map<char, std::vector<char>>;

bool findAvailableStep(const StepsMap &reqMap, char &step) {
	auto min = std::find_if(reqMap.begin(), reqMap.end(),
		[](std::pair<char, std::vector<char>> i) { return i.second.size() == 0; });
	if (min == reqMap.end()) {
		return false;
	}
	step = min->first;
	return true;
}

void removeStepFromReq(StepsMap &reqMap, char step) {
	for (auto &req : reqMap) {
		std::vector<char> &vec = req.second;
		vec.erase(std::remove(vec.begin(), vec.end(), step), vec.end());
	}
}

int calculateJobLen(char step) {
	return 60 + (step - '@');
}

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

	StepsMap reqMap;
	for (const auto& instr : lines) {
		char step = instr[36];
		char reqStep = instr[5];
		reqMap[step].emplace_back(reqStep);
		reqMap.try_emplace(reqStep, std::vector<char>());
	}
	StepsMap reqMap2{ reqMap };

	int stepsTotal = reqMap.size();
	int stepsProccesed = 0;
	string answer;
	char step;
	while (reqMap.size() > 0) {
		bool stepAvail = findAvailableStep(reqMap, step);
		if (stepAvail) {
			stepsProccesed++;
			answer += step;
			reqMap.erase(step);
			removeStepFromReq(reqMap, step);
		}		
	}

	std::cout << "Order of sleigh steps: " << answer << '\n';

	int ticks{ 0 };
	int nWorkers{ 5 };
	std::vector<std::pair<char, int>> activeJobs;
	while(reqMap2.size() > 0 || activeJobs.size() > 0) {
		while (findAvailableStep(reqMap2, step)) {
			// For an available job
			if (activeJobs.size() < nWorkers) {
				//std::cout << ticks << " Pushing work: " << step << ' ' << calculateJobLen(step) << '\n';
				activeJobs.emplace_back(step, calculateJobLen(step));
				// Remove it from the available list, but not from the requirements
				reqMap2.erase(step);
			}
		}
		// Remove 1 tick from jobs
		for (auto &i = activeJobs.begin(); i != activeJobs.end(); ) {
			(*i).second--;
			if ((*i).second == 0) {
				// Once finished, remove the requirement
				removeStepFromReq(reqMap2, (*i).first);
				//std::cout << ticks << " Finishing work: " << (*i).first << '\n'; 
				i = activeJobs.erase(i);
			}
			else {
				i++;
			}
		}
		ticks++;
	}

	std::cout << ticks << '\n';
	return 0;
}
