// Day01.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <string>

using std::string;

int main()
{
	int frequency{ 0 };
	int inputNumber;

	while (std::cin >> inputNumber) {
		frequency += inputNumber;
	}
	std::cout << "Frequency is: " << frequency << '\n';
	return 0;
}
