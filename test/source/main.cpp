#include "ToString.h"

#include "Nira/Parse.h"
#include "Nira/Compose.h"

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "please specify the input file\n";
		return 0;
	}

	if (!std::filesystem::exists(argv[1]))
	{
		std::cout << "file does not exist\n";
		return 0;
	}

	std::string input;
	std::string expectedOutput;
	std::string line;
	std::ifstream file(argv[1]);

	while (std::getline(file, line))
	{
		if (line == "====") 
			break;

		input += line + "\n";
	}

	while (std::getline(file, line))
	{
		expectedOutput += line + "\n";
	}

	Nira::Node node = Nira::Parse(input);
	std::string output = ToString(node);

	if (output != expectedOutput)
	{
		std::cout << "[FAIL] " << argv[1] << "\n";
		std::cout << "expected-output does not match\n";
		std::cout << "expected-output:\n";
		std::cout << expectedOutput;
		std::cout << "output:\n";
		std::cout << output;
		return 0;
	}

	std::cout << "[PASS] " << argv[1] << "\n";

	std::cout << Nira::Compose(node) << "\n";

	return 0;
}
