#include "Nira/Compose.h"

namespace Nira
{
	enum class NodeType
	{
		String,
		List,
		Dictionary,
	};

	void RecursiveCompose(const Nira::Node& node, const size_t depth, const std::string& prefix, std::string& content, bool skippedIndent = false, NodeType previousType = NodeType::String)
	{
		for (size_t i = 1; i < depth && !skippedIndent; ++i)
		{
			content += "  ";
		}

		content += prefix;

		if (node.IsString())
		{
			content += node.AsString() + "\n";
			return;
		}

		if (node.IsList())
		{
			size_t index = 0;
			for (const Nira::Node& child : node.AsList())
			{
				RecursiveCompose(child, depth + 1, "- ", content, previousType == NodeType::List && index == 0, NodeType::List);
				++index;
			}
			return;
		}

		if (node.IsDictionary())
		{
			for (const auto& [key, child] : node.AsDictionary())
				RecursiveCompose(child, depth + 1, key + ": " + (!child.IsString() ? "\n" : ""), content, false, NodeType::Dictionary);
			return;
		}
	}

	std::string Compose(const Node& node)
	{
		std::string content;

		RecursiveCompose(node, 0, "", content);

		return content;
	}
}

