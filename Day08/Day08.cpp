// Day08.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <memory>

using std::string;

std::queue<int> split(const std::string& s, char delimiter) {
	std::queue<int> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.emplace(std::stoi(token));
	}
	return tokens;
}

struct Node {
	std::vector<int> metadata;
	std::vector<std::shared_ptr<Node>> childrens;
};

void processInputTree(std::shared_ptr<Node> node, std::queue<int> &q) {
	int nChildren{ q.front() };
	q.pop();
	int nMetadata{ q.front() };
	q.pop();
	for (int i = 0; i < nChildren; i++) {
		// create node and recurse
		std::shared_ptr<Node> children = std::make_shared<Node>();
		processInputTree(children, q);
		node->childrens.emplace_back(children);
	}
	for (int i = 0; i < nMetadata; i++) {
		node->metadata.emplace_back(q.front());
		q.pop();
	}
}

int sumMetadata(std::shared_ptr<Node> node) {
	int metadata = 0;
	for (const int m : node->metadata) {
		metadata += m;
	}
	for (const auto& c : node->childrens) {
		metadata += sumMetadata(c);
	}
	return metadata;
}

int sumNodeValues(std::shared_ptr<Node> node) {
	int metadata = 0;
	if (node->childrens.size() == 0) {
		for (const int m : node->metadata) {
			metadata += m;
		}
		return metadata;
	}
	for (const int m : node->metadata) {
		try {
			metadata += sumNodeValues(node->childrens.at(m - 1));
		}
		catch (std::exception e) {
			// skip
		}
	}
	return metadata;
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

	std::queue<int> inputVec = split(input, ' ');

	std::shared_ptr<Node> root = std::make_shared<Node>();
	processInputTree(root, inputVec);

	std::cout << "Sum of all metadatas is: " << sumMetadata(root) << '\n';

	std::cout << "Sum of all node values is: " << sumNodeValues(root) << '\n';

	return 0;
}
