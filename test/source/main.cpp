#include "Nira/Parse.h"
#include "Nira/Compose.h"
#include "Nira/Internal/Lexer.h"

#include <fstream>
#include <iostream>

std::string Quote(const std::string& content)
{
	std::string quoted = "\"";

	for (char letter: content)
	{
		switch (letter) 
		{
			case '\t':
				quoted += "\\t";
				break;

			case '\n':
				quoted += "\\n";
				break;

			case '"':
				quoted += "\\\"";
				break;

			default:
				quoted += letter;
				break;
		}
	}

	quoted += "\"";

	return quoted;
}

std::string ToString(const Nira::Node& node, size_t depth = 0, const std::string prefix = "")
{
	std::string content;

	for (size_t i = 0; i < depth; ++i)
		content += "  ";

	content += prefix;

	if (node.isString())
		return content + "String(" + Quote(node.asString()) + ")\n";

	if (node.isArray())
	{
		content += "Array:\n";

		for (size_t i = 0; i < node.size(); ++i)
			content += ToString(node[i], depth + 1, std::to_string(i) + ": ");

		return content;
	}

	if (node.isMap())
	{
		content += "Map:\n";

		for (const auto& [key, node] : node.asMap())
			content += ToString(node, depth + 1, Quote(key) + ": ");

		return content;
	}

	return content;
}


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

	Nira::Node node = Nira::parse(input);
	std::string output = ToString(node);

	if (output != expectedOutput)
	{
		std::cout << "[FAIL] " << argv[1] << "\n";
		std::cout << "expected-output:\n";
		std::cout << expectedOutput;

		// std::cout << "\noutput-tokens:\n";
		//
		// Nira::Internal::Lexer lexer;
		// lexer.Tokenize(input);
		// for (size_t i = 0; i < lexer.GetTokenCount(); ++i)
		// {
		// 	const Nira::Internal::Token& token = lexer.GetToken(i);
		// 	switch (token.type)
		// 	{
		// 		case Nira::Internal::TokenType::Newline:
		// 			std::cout << "Newline\n";
		// 			break;
		// 		case Nira::Internal::TokenType::Bullet:
		// 			std::cout << "Bullet\n";
		// 			break;
		// 		case Nira::Internal::TokenType::Colon:
		// 			std::cout << "Colon\n";
		// 			break;
		// 		case Nira::Internal::TokenType::IndentIncr:
		// 			std::cout << "IndentIncr\n";
		// 			break;
		// 		case Nira::Internal::TokenType::IndentDecr:
		// 			std::cout << "IndentDecr\n";
		// 			break;
		// 		case Nira::Internal::TokenType::String:
		// 			std::cout << "String(" << std::quoted(token.content) << ")\n";
		// 			break;
		// 		case Nira::Internal::TokenType::StringCon:
		// 			std::cout << "StringCon(" << std::quoted(token.content) << ")\n";
		// 			break;
		// 	}
		// }

		std::cout << "\noutput-tree:\n";
		std::cout << output;
		return 0;
	}

	std::cout << "[PASS] " << argv[1] << "\n";

	return 0;
}
