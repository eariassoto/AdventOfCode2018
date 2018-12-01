// Day01.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using std::string;

int main()
{
	std::vector<int> inputList;
	int frequency{ 0 };
	int inputNumber;

	while (std::cin >> inputNumber) {
		inputList.push_back(inputNumber);
	}

	/* find final freq (puzzle 1)
	for (const auto n : inputList) {
		frequency += n;
	}
	*/

	// find first repeated frequency, need to iterate the list 1+ times
	std::unordered_set<int> foundFreq;
	auto listIt = inputList.begin();
	for (;;) {
		// Alter freq
		frequency += *listIt;

		if (foundFreq.find(frequency) != foundFreq.end()) {
			// Repeated freq found
			break;
		}
		else {
			// Add to lookup set
			foundFreq.insert(frequency);
		}

		listIt++;
		// Make it circular
		if (listIt == inputList.end()) {
			listIt = inputList.begin();
		}
	}


	std::cout << "Repeated frequency is: " << frequency << '\n';
	return 0;
}
