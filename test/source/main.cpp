#include "Nira/Internal/Lexer.h"
#include "Nira/compose.h"
#include "Nira/parse.h"

#include <fstream>
#include <iostream>

std::string quote(const std::string& content) {
	std::string quoted = "\"";

	for (char letter : content) {
		switch (letter) {
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

std::string toString(const Nira::Node& node, size_t depth = 0, const std::string prefix = "") {
	std::string content;

	for (size_t i = 0; i < depth; ++i)
		content += "  ";

	content += prefix;

	if (node.isString())
		return content + "String(" + quote(node.asString()) + ")\n";

	if (node.isArray()) {
		content += "Array:\n";

		for (size_t i = 0; i < node.size(); ++i)
			content += toString(node[i], depth + 1, std::to_string(i) + ": ");

		return content;
	}

	if (node.isMap()) {
		content += "Map:\n";

		for (const auto& [key, node] : node.asMap())
			content += toString(node, depth + 1, quote(key) + ": ");

		return content;
	}

	return content;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "please specify the input file\n";
		return 0;
	}

	if (!std::filesystem::exists(argv[1])) {
		std::cout << "file does not exist\n";
		return 0;
	}

	std::string input;
	std::string expectedOutput;
	std::string line;
	std::ifstream file(argv[1]);

	while (std::getline(file, line)) {
		if (line == "====")
			break;

		input += line + "\n";
	}

	while (std::getline(file, line)) {
		expectedOutput += line + "\n";
	}

	Nira::Node node = Nira::parse(input);
	std::string output = toString(node);

	if (output != expectedOutput) {
		std::cout << "[FAIL] " << argv[1] << "\n";
		std::cout << "expected-output:\n";
		std::cout << expectedOutput;
		std::cout << "output:\n";
		std::cout << output;
		return 0;
	}

	std::cout << "[PASS] " << argv[1] << "\n";

	return 0;
}
