#include "Nira/Parse.h"

#include "Nira/Internal/Lexer.h"

namespace Nira {
	class Parser {
	public:
		void parse(const std::string& content) {
			_indent = 0;
			_tokenIndex = 0;
			_lexer.parse(content);
			_heads.push_back(&_root);

			while (isBound(0)) {
				switch (getToken(0).type) {
					case Internal::TokenType::newline:
						if (_heads.size() > 1)
							_heads.pop_back();

						advance(1);
						break;

					case Internal::TokenType::indentIncr:
					case Internal::TokenType::indentDecr:
						if (getToken(0).type == Internal::TokenType::indentIncr) {
							while (isBound(0) && getToken(0).type == Internal::TokenType::indentIncr) {
								++_indent;
								advance(1);
							}
						} else {
							while (isBound(0) && getToken(0).type == Internal::TokenType::indentDecr) {
								--_indent;
								advance(1);
							}
						}

						while (_indent + 1 < _heads.size() && _heads.size() > 1)
							_heads.pop_back();
						break;

					case Internal::TokenType::string:
						if (isBound(1) && getToken(1).type == Internal::TokenType::colon) {
							Node& value = (*_heads.back())[getToken(0).content] = Node();
							_heads.push_back(&value);

							advance(2);

							if (isBound(0) && getToken(0).type == Internal::TokenType::newline) {
								advance(1);
							}

							break;
						}

						*_heads.back() = getToken(0).content;

						advance(1);
						break;

					case Internal::TokenType::stringCon: {
						size_t indentPosition = (_heads.size() - 1) * 2;
						*_heads.back() = _heads.back()->asString() + getToken(0).content.substr(indentPosition);
						advance(1);
						break;
					}

					case Internal::TokenType::bullet:
						_heads.back()->add(Node());
						_heads.push_back(&(*_heads.back())[_heads.back()->size() - 1]);

						advance(1);
						break;

					default:
						advance(1);
						break;
				}
			}
		}

		const Node& getRoot() {
			return _root;
		}

	private:
		bool isBound(size_t offset) {
			return (_tokenIndex + offset) < _lexer.getTokenSize();
		}

		void advance(size_t offset) {
			_tokenIndex += offset;
		}

		const Internal::Token& getToken(size_t offset) {
			return _lexer.getToken(_tokenIndex + offset);
		}

	private:
		Node _root;
		size_t _tokenIndex;
		size_t _indent;
		Internal::Lexer _lexer;
		std::vector<Node*> _heads;
	};

	Node parse(const std::string& content) {
		Parser parser;
		parser.parse(content);

		return parser.getRoot();
	}
}
