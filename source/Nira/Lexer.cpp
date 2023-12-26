#include "Nira/Lexer.h"

namespace Nira
{
	void Lexer::Tokenize(const std::string& input)
	{
		_previousIndent = 0;
		_index = 0;
		_input = input;
		_tokens.clear();

		OnNewline();

		while (IsBound())
		{
			switch (GetByte(0))
			{
				case '\n': 
				{
					while (IsBound() && GetByte(0) == '\n') Advance(1);

					Token token;
					token.type = TokenType::Newline;
					_tokens.push_back(token);
					OnNewline();
					break;
				}

				case ':': 
				{
					if (GetByte(1) == ' ')
					{
						Token token;
						token.type = TokenType::Colon;
						_tokens.push_back(token);
						Advance(2);
						break;
					}

					if (GetByte(1) == '\n')
					{
						Token token;
						token.type = TokenType::Colon;
						token.content = ":";
						_tokens.push_back(token);
						Advance(1);
						break;
					}

					ConsumeString();
					break;
				}

				default:
					ConsumeString();
					break;
			}
		}
	}

	const Token& Lexer::GetToken(size_t index) const
	{
		return _tokens[index];
	}

	size_t Lexer::GetTokenCount()
	{
		return _tokens.size();
	}

	bool Lexer::IsBound()
	{
		return _index < _input.size();
	}

	void Lexer::Advance(size_t offset)
	{
		_index += offset;
	}

	char Lexer::GetByte(size_t offset)
	{
		return _input[_index + offset];
	}

	void Lexer::ConsumeString()
	{
		if (_tokens.empty() || _tokens.back().type != TokenType::String)
		{
			Token token;
			token.type = TokenType::String;
			_tokens.push_back(token);
		}

		do
		{
			_tokens.back().content += GetByte(0);
			Advance(1);
		} while (IsBound() && GetByte(0) != '\n' && GetByte(0) != ':');
	}

	void Lexer::OnNewline()
	{
		size_t spaceCount = 0;

		while (IsBound() && GetByte(0) == ' ')
		{
			Advance(1);
			++spaceCount;
		}

		size_t currentIndent = spaceCount / 2;

		if (_previousIndent < currentIndent)
		{
			for (size_t i = 0; i < (currentIndent - _previousIndent); ++i) 
			{
				Token token;
				token.type = TokenType::IndentIncr;
				_tokens.push_back(token);
			}
			_previousIndent = currentIndent;
		}

		if (_previousIndent > currentIndent)
		{
			for (size_t i = 0; i < (_previousIndent - currentIndent); ++i) 
			{
				Token token;
				token.type = TokenType::IndentDecr;
				_tokens.push_back(token);
			}
			_previousIndent = currentIndent;
		}

		while (GetByte(0) == '-' && GetByte(1) == ' ') {
			Token token;
			token.type = TokenType::Bullet;
			_tokens.push_back(token);
			Advance(2);
		}
	}
}

