#pragma once

#include "Nira/Node.h"

std::string ToString(const Nira::Node& node, size_t depth = 0, const std::string prefix = "")
{
	std::string content;

	for (size_t i = 0; i < depth; ++i)
		content += "  ";

	content += prefix;

	if (node.IsString())
		return content + "String(" + node.AsString() + ")\n";

	if (node.IsList())
	{
		content += "List:\n";

		for (size_t i = 0; i < node.Size(); ++i)
			content += ToString(node[i], depth + 1, std::to_string(i) + ": ");

		return content;
	}

	if (node.IsDictionary())
	{
		content += "Dictionary:\n";

		for (const auto& [key, node] : node.AsDictionary())
			content += ToString(node, depth + 1, key + ": ");

		return content;
	}

	return content;
}

