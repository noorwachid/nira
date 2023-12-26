#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Nira
{
	enum class TokenType
	{
		String,
		StringCon,
		Colon,
		Bullet,
		Newline,
		IndentIncr,
		IndentDecr,
	};

	struct Token
	{
		TokenType type;
		std::string content;
	};

	class Lexer
	{
	public:
		void Tokenize(const std::string& input);

		const Token& GetToken(size_t index) const;

		size_t GetTokenCount();

	private:
		bool IsBound();

		void Advance(size_t offset);

		char GetByte(size_t offset);

		void ConsumeString();

		void OnNewline();

	private:
		bool _keyPart;
		size_t _index;
		std::string _input;
		std::vector<Token> _tokens;

		size_t _previousIndent;
	};
}

