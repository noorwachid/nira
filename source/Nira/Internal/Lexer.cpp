#include "Nira/Internal/Lexer.h"

namespace Nira::Internal {
	void Lexer::parse(const std::string& input) {
		_keyPart = true;
		_previousIndent = 0;
		_index = 0;
		_input = input;
		_tokens.clear();

		onNewline();

		while (isBound()) {
			switch (getByte(0)) {
				case '\n': {
					while (isBound() && getByte(0) == '\n')
						advance(1);

					if (_tokens.empty() || _tokens.back().type != TokenType::newline) {
						Token token;
						token.type = TokenType::newline;
						_tokens.push_back(token);
					}

					onNewline();
					break;
				}

				case ':': {
					if (_keyPart) {
						if (getByte(1) == ' ') {
							Token token;
							token.type = TokenType::colon;
							_tokens.push_back(token);
							_keyPart = false;
							advance(2);
							break;
						}

						if (getByte(1) == '\n') {
							Token token;
							token.type = TokenType::colon;
							token.content = ":";
							_tokens.push_back(token);
							advance(1);
							break;
						}
					}

					consumeString();
					break;
				}

				case '#':
					while (isBound() && getByte(0) != '\n')
						advance(1);
					break;

				default:
					consumeString();
					break;
			}
		}
	}

	const Token& Lexer::getToken(size_t index) const {
		return _tokens[index];
	}

	size_t Lexer::getTokenSize() {
		return _tokens.size();
	}

	bool Lexer::isBound() {
		return _index < _input.size();
	}

	void Lexer::advance(size_t offset) {
		_index += offset;
	}

	char Lexer::getByte(size_t offset) {
		return _input[_index + offset];
	}

	void Lexer::consumeString() {
		Token token;
		token.type = TokenType::string;
		_tokens.push_back(token);

		while (isBound()) {
			switch (getByte(0)) {
				// escaping characters
				case '\\':
					switch (getByte(1)) {
						case ':':
						case '-':
						case '#':
						case '\\':
							_tokens.back().content += getByte(1);
							advance(2);
							break;

						case '\n': {
							advance(2);
							Token token;
							token.type = TokenType::stringCon;
							_tokens.push_back(token);
							break;
						}

						default:
							_tokens.back().content += getByte(0);
							_tokens.back().content += getByte(1);
							advance(2);
							break;
					}
					break;

				case '\n':
				case '#':
					return;

				case ':':
					if (_keyPart)
						return;

					_tokens.back().content += getByte(0);
					advance(1);
					break;

				default:
					_tokens.back().content += getByte(0);
					advance(1);
					break;
			}
		}
	}

	void Lexer::onNewline() {
		_keyPart = true;
		size_t spaceCount = 0;

		while (isBound() && getByte(0) == ' ') {
			advance(1);
			++spaceCount;
		}

		size_t currentIndent = spaceCount / 2;

		if (_previousIndent < currentIndent) {
			for (size_t i = 0; i < (currentIndent - _previousIndent); ++i) {
				Token token;
				token.type = TokenType::indentIncr;
				_tokens.push_back(token);
			}
			_previousIndent = currentIndent;
		}

		if (_previousIndent > currentIndent) {
			for (size_t i = 0; i < (_previousIndent - currentIndent); ++i) {
				Token token;
				token.type = TokenType::indentDecr;
				_tokens.push_back(token);
			}
			_previousIndent = currentIndent;
		}

		while (getByte(0) == '-' && getByte(1) == ' ') {
			Token token;
			token.type = TokenType::bullet;
			_tokens.push_back(token);
			advance(2);
		}
	}
}
