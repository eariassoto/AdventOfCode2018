#include <iostream>
#include <vector>
#include <unordered_map>

using MarbleIt = std::vector<int>::const_iterator;
using MarbleVec = std::vector<int>;

MarbleIt
rotateClockwise(const MarbleVec &vec, MarbleIt &it, int n) {
	MarbleIt newIt = it;
	for (int i = 0; i < n; i++) {
		newIt++;
		if (newIt == vec.end()) {
			newIt = vec.begin();
		}
	}
	return newIt;
}

MarbleIt
rotateCounterClockwise(const MarbleVec &vec, MarbleIt &it, int n) {
	MarbleIt newIt = it;
	
	for (int i = 0; i < n; i++) {
		if (newIt == vec.begin()) {
			newIt = vec.end();
		}
		newIt--;
	}
	return newIt;
}

void
addMarble(MarbleVec &vec, MarbleIt &currentMarble, int value) {
	if (vec.size() == 1) {
		currentMarble = vec.insert(vec.end(), value);
	}
	else if (vec.size() == 2) {
		currentMarble = vec.insert(vec.end() - 1, value);
	}
	else {
		MarbleIt newPos = rotateClockwise(vec, currentMarble, 2);
		currentMarble = vec.emplace(newPos, value);
	}
}

int main(int argc, char* argv[]) {
	// TODO: get from argv
	int numPlayers{ 439 };
	int higestMarble{ 71307 }; 
	
	MarbleVec gameMarbles{ 0 };
	MarbleIt currentMarble = gameMarbles.begin();

	int playerInTurn{ 1 };
	int lowestMarble{ 1 };

	std::unordered_map<int, int> scores;

	while (lowestMarble != higestMarble) {
		if (lowestMarble % 23 != 0) {
			addMarble(gameMarbles, currentMarble, lowestMarble);
		}
		else {
			scores[playerInTurn] += lowestMarble;
			MarbleIt it = rotateCounterClockwise(gameMarbles, currentMarble, 7);
			scores[playerInTurn] += *it;
			currentMarble = gameMarbles.erase(it);
			if (currentMarble == gameMarbles.end()) {
				currentMarble = gameMarbles.begin();
			}
		}

		playerInTurn++;
		if (playerInTurn == (numPlayers + 1)) {
			playerInTurn = 1;
		}
		lowestMarble++;
	}

	int maxScore = 0;
	for (const auto& score : scores) {
		if (score.second > maxScore) {
			maxScore = score.second;
		}
	}

	std::cout << maxScore << '\n';
	return 0;

}