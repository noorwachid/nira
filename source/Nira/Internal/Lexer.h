#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Nira::Internal {
	enum class TokenType {
		string,
		stringCon,
		colon,
		bullet,
		newline,
		indentIncr,
		indentDecr,
	};

	struct Token {
		TokenType type;
		std::string content;
	};

	class Lexer {
	public:
		void parse(const std::string& input);

		const Token& getToken(size_t index) const;

		size_t getTokenSize();

	private:
		bool isBound();

		void advance(size_t offset);

		char getByte(size_t offset);

		void consumeString();

		void onNewline();

	private:
		bool _keyPart;
		size_t _index;
		std::string _input;
		std::vector<Token> _tokens;

		size_t _previousIndent;
	};
}
