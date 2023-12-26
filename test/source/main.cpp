#include "ToString.h"

#include "Nira/Lexer.h"
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
		std::cout << "expected-output:\n";
		std::cout << expectedOutput;
		std::cout << "\noutput-tokens:\n";

		Nira::Lexer lexer;
		lexer.Tokenize(input);
		for (size_t i = 0; i < lexer.GetTokenCount(); ++i)
		{
			const Nira::Token& token = lexer.GetToken(i);
			switch (token.type)
			{
				case Nira::TokenType::Newline:
					std::cout << "Newline\n";
					break;
				case Nira::TokenType::Bullet:
					std::cout << "Bullet\n";
					break;
				case Nira::TokenType::Colon:
					std::cout << "Colon\n";
					break;
				case Nira::TokenType::IndentIncr:
					std::cout << "IndentIncr\n";
					break;
				case Nira::TokenType::IndentDecr:
					std::cout << "IndentDecr\n";
					break;
				case Nira::TokenType::String:
					std::cout << "String(" << token.content << ")\n";
					break;
				case Nira::TokenType::StringCon:
					std::cout << "StringCon(" << token.content << ")\n";
					break;
			}
		}

		std::cout << "\noutput-tree:\n";
		std::cout << output;
		return 0;
	}

	std::cout << "[PASS] " << argv[1] << "\n";

	return 0;
}
