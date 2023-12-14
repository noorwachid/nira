#include "Nira/Lexer.h"
#include "Nira/Parse.h"

namespace Nira
{
	class Parser
	{
	public:
		Node node;

	public:
		void Parse(const std::string& content)
		{
			_tokenIndex = 0;
			_lexer.Tokenize(content);
			_heads.push_back(&node);

			while (InBound(0))
			{
				if (InBound(1) && GetToken(0).type == TokenType::String && GetToken(1).type == TokenType::Colon)
				{
					(*_heads.back()) [GetToken(0).content] = Node();

					_heads.push_back(&(*_heads.back())[GetToken(0).content]);
					Advance(2);
					continue;
				}

				if (GetToken(0).type == TokenType::Bullet)
				{
					(*_heads.back()).Add(Node());

					_heads.push_back(&(*_heads.back()).At(-1));
					Advance(1);
					continue;
				}

				if (GetToken(0).type == TokenType::Newline)
				{
					if (InBound(1)) 
					{
						if (GetToken(1).type == TokenType::IndentInc)
						{
							Advance(2);
							continue;
						}

						if (GetToken(1).type == TokenType::IndentDecr)
						{
							Advance(2);

							if (_heads.size() > 2)
							{
								_heads.pop_back();
								_heads.pop_back();
							}

							continue;
						}
					}

					if (_heads.size() > 1)
						_heads.pop_back();

					Advance(1);
					continue;
				}

				(*_heads.back()) = GetToken(0).content;

				Advance(1);
			}
		}

	private:
		bool InBound(size_t offset)
		{
			return (_tokenIndex + offset) < _lexer.GetTokenCount();
		}

		void Advance(size_t offset)
		{
			_tokenIndex += offset;
		}

		const Token& GetToken(size_t offset)
		{
			return _lexer.GetToken(_tokenIndex + offset);
		}

	private:
		size_t _tokenIndex;
		Lexer _lexer;
		std::vector<Node*> _heads;
	};

	Node Parse(const std::string& content)
	{
		Parser parser;
		parser.Parse(content);

		return parser.node;
	}
}
