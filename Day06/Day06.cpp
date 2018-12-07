#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>
#include <unordered_map>

using std::string;

std::vector<string> split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

struct Point {
	Point(int id, int x, int y) : id{ id }, x{ x }, y{ y }, isOuter{ false }{}
	
	int getIdForClosestPoint(const std::vector<Point>& points);
	int id;
	int x;
	int y;
	bool isOuter;

private:
	int calculateManhattanDistance(const Point &otherPoint);
};

int
Point::calculateManhattanDistance(const Point &otherPoint) {
	return (int)( abs((double)(otherPoint.x - this->x)) + abs((double)(otherPoint.y - this->y)) );
}

int
Point::getIdForClosestPoint(const std::vector<Point>& points) {
	std::vector<std::pair<int, int>> distanceList;
	for (const Point &otherPoint : points) {
		int distance = calculateManhattanDistance(otherPoint);
		distanceList.emplace_back(std::make_pair(distance, otherPoint.id));
	}
	std::sort(distanceList.begin(), distanceList.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
        return a.first < b.first;   
    });
	if (distanceList[0].first == distanceList[1].first)
		return -1;
	return distanceList[0].second;
}


int main(int argc, char *argv[]) {
	string input;
	std::vector<Point> points;

	if (argc == 2) {
		std::ifstream inputFile{ argv[1] };
		if (!inputFile.is_open()) {
			std::cout << "Could not open input file\n";
			return 0;
		}
		int i = 0;
		while (std::getline(inputFile, input)) {
			if (input.size() > 0) {
				auto numbers = split(input, ',');
				points.emplace_back(Point{ i++, std::stoi(numbers[0]), std::stoi(numbers[1]) });
			}
		}
	}
	else {
		int i = 0;
		while (std::cin >> input) {
			auto numbers = split(input, ',');
			points.emplace_back(Point{ i++, std::stoi(numbers[0]), std::stoi(numbers[1]) });
		}
	}

	int minX = std::numeric_limits<int>::max();
	int minY = std::numeric_limits<int>::max();
	int maxX = 0;
	int maxY = 0;

	for (const Point &p : points) {
		if (p.x > maxX)
			maxX = p.x;
		if (p.x < minX)
			minX = p.x;
		if (p.y > maxY)
			maxY = p.y;
		if (p.y < minY)
			minY = p.y;
	}

	std::unordered_map<int, int> distanceMap;
	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			Point tmp{ -1, x, y };
			int closestId = tmp.getIdForClosestPoint(points);
	
			// If the point is in the outer join, identify the closest coord as infinite
			if (closestId != -1 && (x == minX || x == maxX || y == minY || y == maxY)) {
				points[closestId].isOuter = true;
			}
			distanceMap[closestId] += 1;
		}
	}

	int largestArea = 0;
	int largestAreaId = 0;

	for (const Point &p : points) {
		if (p.isOuter) {
			continue;
		}
		if (distanceMap[p.id] > largestArea) {
			largestArea = distanceMap[p.id];
			largestAreaId = p.id;
		}
	}
	std::cout << distanceMap[largestAreaId] << '\n';

	return 0;
}
