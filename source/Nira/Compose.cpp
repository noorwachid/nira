#include "Nira/Compose.h"

namespace Nira
{
	void RecursiveCompose(const Nira::Node& node, const size_t depth, const std::string& prefix, std::string& content)
	{
		for (size_t i = 1; i < depth; ++i)
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
			for (const Nira::Node& child : node.AsList())
				RecursiveCompose(child, depth + 1, "- ", content);
			return;
		}

		if (node.IsDictionary())
		{
			for (const auto& [key, child] : node.AsDictionary())
				RecursiveCompose(child, depth + 1, key + ": " + (!child.IsString() ? "\n" : ""), content);
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

