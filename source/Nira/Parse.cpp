#include "Nira/Parse.h"
#include "Nira/Internal/Lexer.h"

namespace Nira
{
	class Parser
	{
	public:
		void Parse(const std::string& content)
		{
			_indent = 0;
			_tokenIndex = 0;
			_lexer.Tokenize(content);
			_heads.push_back(&_root);

			while (IsBound(0))
			{
				switch (GetToken(0).type)
				{
					case Internal::TokenType::Newline:
						if (_heads.size() > 1)
							_heads.pop_back();

						Advance(1);
						break;

					case Internal::TokenType::IndentIncr:
					case Internal::TokenType::IndentDecr:
						if (GetToken(0).type == Internal::TokenType::IndentIncr)
						{
							while (IsBound(0) && GetToken(0).type == Internal::TokenType::IndentIncr)
							{
								++_indent;
								Advance(1);
							}
						} 
						else 
						{
							while (IsBound(0) && GetToken(0).type == Internal::TokenType::IndentDecr)
							{
								--_indent;
								Advance(1);
							}
						}

						while (_indent + 1 < _heads.size() && _heads.size() > 1) 
							_heads.pop_back();
						break;

					case Internal::TokenType::String:
						if (IsBound(1) && GetToken(1).type == Internal::TokenType::Colon)
						{
							Node& value = (*_heads.back())[GetToken(0).content] = Node();
							_heads.push_back(&value);

							Advance(2);

							if (IsBound(0) && GetToken(0).type == Internal::TokenType::Newline)
							{
								Advance(1);
							}

							break;
						}

						*_heads.back() = GetToken(0).content;

						Advance(1);
						break;

					case Internal::TokenType::StringCon:
					{
						size_t indentPosition = (_heads.size() - 1) * 2;
						*_heads.back() = _heads.back()->AsString() + GetToken(0).content.substr(indentPosition);
						Advance(1);
						break;
					}
						

					case Internal::TokenType::Bullet:
						_heads.back()->Add(Node());
						_heads.push_back(&(*_heads.back())[_heads.back()->Size() - 1]);

						Advance(1);
						break;

					default:
						Advance(1);
						break;
				}
			}
		}

		const Node& GetRoot()
		{
			return _root;
		}

	private:
		bool IsBound(size_t offset)
		{
			return (_tokenIndex + offset) < _lexer.GetTokenCount();
		}

		void Advance(size_t offset)
		{
			_tokenIndex += offset;
		}

		const Internal::Token& GetToken(size_t offset)
		{
			return _lexer.GetToken(_tokenIndex + offset);
		}

	private:
		Node _root;
		size_t _tokenIndex;
		size_t _indent;
		Internal::Lexer _lexer;
		std::vector<Node*> _heads;
	};

	Node Parse(const std::string& content)
	{
		Parser parser;
		parser.Parse(content);

		return parser.GetRoot();
	}
}
