// Day03.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <algorithm>

using std::string;


struct Guard {
	Guard(int id);
	void changeState(int minute);
	int minuteMoreSleep();
	int id;
	bool isAwake;
	int minuteWentSleep;
	int minutesAsleep;
	std::unordered_map<int, int> minutesSleepMap;
};
using GuardPtr = std::shared_ptr<Guard>;

Guard::Guard(int id) : id{ id }, isAwake{ true }, minuteWentSleep{ 0 }, minutesAsleep{ 0 } {}

void
Guard::changeState(int minute) {
	if (isAwake) {
		isAwake = false;
		minuteWentSleep = minute;
	}
	else {
		for (int i = minuteWentSleep; i < minute; i++) {
			minutesSleepMap[i]++;
			minutesAsleep++;
		}
		isAwake = true;
	}
}

int
Guard::minuteMoreSleep() {
	auto x = std::max_element(minutesSleepMap.begin(), minutesSleepMap.end(),
		[](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
		return p1.second < p2.second; });
	return x->first;
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

	// Input format:
	//+2239
	//19
	//37
	//44
	//54
	// Where +# is a guard ID, and the following numbers are the asleep/wake up times
	// Input was ordered with a bash script
	int lastGuardId = 0;
	std::unordered_map<int, GuardPtr> guardsMap;
	for (const auto& line : lines) {
		if (line[0] == '+') {
			lastGuardId = std::stoi(line);
			auto it = guardsMap.find(lastGuardId);
			if (it == guardsMap.end()) {
				guardsMap.emplace(lastGuardId, std::make_shared<Guard>( lastGuardId ));
			}
		}
		else {
			guardsMap[lastGuardId]->changeState(std::stoi(line));
		}
	}

	auto cmp = [](std::pair<int, GuardPtr> i, std::pair<int, GuardPtr> j) { return i.second->minutesAsleep < j.second->minutesAsleep; };
	auto largest = std::max_element(guardsMap.begin(), guardsMap.end(), cmp);

	int minutesAsleep = largest->second->minutesAsleep;
	int minuteMoreSleep = largest->second->minuteMoreSleep();
	std::cout << "The guard with more minutes asleep (" << minutesAsleep << ") is: " << largest->second->id << '\n';
	std::cout << "This guard sleep the most times at minute: " << minuteMoreSleep << '\n';
	std::cout << "Strategy 1: " << minuteMoreSleep * largest->second->id;
	return 0;
}
