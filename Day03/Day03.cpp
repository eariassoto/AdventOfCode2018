// Day03.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using std::string;

namespace std {
	template <> struct hash<std::pair<int, int>> {
		inline size_t operator()(const std::pair<int, int> &v) const {
			std::hash<int> int_hasher;
			return int_hasher(v.first) ^ int_hasher(v.second);
		}
	};
}

std::vector<string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

struct Rectangle {
	Rectangle();
	Rectangle(const string &input);
	Rectangle(int x, int y, int width, int height);
	int id;
	int x;
	int y;
	int width;
	int height;
};

Rectangle::Rectangle(const string &input) {
	string str{ input };
	str.erase(std::remove(str.begin(), str.end(), '#'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '@'), str.end());
	str.erase(std::remove(str.begin(), str.end(), ':'), str.end());

	auto tokens = split(str, ' ');
	id = std::stoi(tokens[0]);

	auto origin = split(tokens[2], ',');
	x = std::stoi(origin[0]);
	y = std::stoi(origin[1]);
	auto size = split(tokens[3], 'x');
	width = std::stoi(size[0]);
	height = std::stoi(size[1]);
}


Rectangle::Rectangle(int x, int y, int width, int height):
	x{ x }, y{ y }, width{ width }, height{ height } {}

Rectangle::Rectangle() :
	x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 } {}


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
	}
	else {
		while (std::cin >> l) {
			lines.push_back(l);
		}
	}

	std::vector<Rectangle> rectangles;
	for (const auto& line : lines) {
		rectangles.push_back(Rectangle{ line });
	}

	std::unordered_map<std::pair<int, int>, int> overMap;
	for (const auto &rect : rectangles) {
		for (int i = rect.x; i < (rect.x + rect.width); i++) {
			for (int j = rect.y; j < (rect.y + rect.height); j++) {
				auto p = std::make_pair(i, j);
				overMap[p] += 1;
			}
		}
	}

	auto overlappedSquares = count_if(overMap.begin(), overMap.end(), [](auto &p) {
		return p.second > 1;
	});

	std::cout << "Overlapped area is: " << overlappedSquares << '\n';
	return 0;
}
