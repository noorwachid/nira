#include "Nira/Lexer.h"
#include "Nira/Parse.h"
#include "Nira/Compose.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

const char* ToNullString(Nira::TokenType type) {
	switch (type) {
		case Nira::TokenType::String: return "String";
		case Nira::TokenType::Colon: return "Colon";
		case Nira::TokenType::Bullet: return "Bullet";
		case Nira::TokenType::Newline: return "Newline";
		case Nira::TokenType::IndentInc: return "IndentInc";
		case Nira::TokenType::IndentDecr: return "IndentDecr";
	}
}

void DebugNode(const Nira::Node& node, size_t depth = 0, const std::string prefix = "") {
	for (size_t i = 0; i < depth; ++i) {
		std::cout << "  ";
	}

	std::cout << prefix;

	if (node.IsString()) {
		std::cout << "String(" << node.AsString() << ")\n";
		return;
	}

	if (node.IsList()) {
		std::cout << "List:\n";
		for (size_t i = 0; i < node.Size(); ++i) {
			DebugNode(node[i], depth + 1, std::to_string(i) + ": ");
		}
		return;
	}

	if (node.IsDictionary()) {
		std::cout << "Dictionary: " << node.AsString() << "\n";
		for (const auto& [key, node] : node.AsDictionary()) {
			DebugNode(node, depth + 1, key + ": ");
		}
		return;
	}
}

int main()
{
	std::string content = R"(
- - - A
    - B
    - C
)";

	Nira::Lexer lexer;
	lexer.Tokenize(content);

	std::cout << "\n[LEXER]\n";

	for (size_t i = 0; i < lexer.GetTokenCount(); ++i) {
		std::cout << ToNullString(lexer.GetToken(i).type) << ": " << lexer.GetToken(i).content << "\n";
	}

	std::cout << "\n[TREE]\n";

	DebugNode(Nira::Parse(content));

	return 0;
}
