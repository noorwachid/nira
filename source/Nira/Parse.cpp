#include "Nira/Lexer.h"
#include "Nira/Parse.h"

void DebugNode(const Nira::Node& node, size_t depth = 0, const std::string prefix = "")
{
	for (size_t i = 0; i < depth; ++i)
	{
		std::cout << "  ";
	}

	std::cout << prefix;

	if (node.IsString())
	{
		std::cout << "String(" << node.AsString() << ")\n";
		return;
	}

	if (node.IsList())
	{
		std::cout << "List:\n";
		for (size_t i = 0; i < node.Size(); ++i)
		{
			DebugNode(node[i], depth + 1, std::to_string(i) + ": ");
		}
		return;
	}

	if (node.IsDictionary())
	{
		std::cout << "Dictionary: " << "\n";
		for (const auto& [key, node] : node.AsDictionary())
		{
			DebugNode(node, depth + 1, key + ": ");
		}
		return;
	}
}

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
					case TokenType::Newline:
						if (_heads.size() > 1)
							_heads.pop_back();

						Advance(1);
						break;

					case TokenType::IndentIncr:
					case TokenType::IndentDecr:
						if (GetToken(0).type == TokenType::IndentIncr)
						{
							while (IsBound(0) && GetToken(0).type == TokenType::IndentIncr)
							{
								++_indent;
								Advance(1);
							}
						} 
						else 
						{
							while (IsBound(0) && GetToken(0).type == TokenType::IndentDecr)
							{
								--_indent;
								Advance(1);
							}
						}

						while (_indent + 1 < _heads.size() && _heads.size() > 1) 
							_heads.pop_back();
						break;

					case TokenType::String:
						if (IsBound(1) && GetToken(1).type == TokenType::Colon)
						{
							Node& value = (*_heads.back())[GetToken(0).content] = Node();
							_heads.push_back(&value);

							Advance(2);

							if (IsBound(0) && GetToken(0).type == TokenType::Newline)
							{
								Advance(1);
							}

							break;
						}

						*_heads.back() = GetToken(0).content;
						Advance(1);
						break;

					case TokenType::Bullet:
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

		const Token& GetToken(size_t offset)
		{
			return _lexer.GetToken(_tokenIndex + offset);
		}

	private:
		Node _root;
		size_t _tokenIndex;
		size_t _indent;
		Lexer _lexer;
		std::vector<Node*> _heads;
	};

	Node Parse(const std::string& content)
	{
		Parser parser;
		parser.Parse(content);

		return parser.GetRoot();
	}
}
