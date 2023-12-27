#include "Nira/Compose.h"

namespace Nira {
	enum class NodeType {
		string,
		array,
		map,
	};

	void recursiveCompose(
		const Nira::Node& node, const size_t depth, const std::string& prefix, std::string& content,
		bool skippedIndent = false, NodeType previousType = NodeType::string
	) {
		for (size_t i = 1; i < depth && !skippedIndent; ++i) {
			content += "  ";
		}

		content += prefix;

		if (node.isString()) {
			content += node.asString() + "\n";
			return;
		}

		if (node.isArray()) {
			size_t index = 0;
			for (const Nira::Node& child : node.asArray()) {
				recursiveCompose(
					child, depth + 1, "- ", content, previousType == NodeType::array && index == 0, NodeType::array
				);
				++index;
			}
			return;
		}

		if (node.isMap()) {
			for (const auto& [key, child] : node.asMap())
				recursiveCompose(
					child, depth + 1, key + ": " + (!child.isString() ? "\n" : ""), content, false, NodeType::map
				);
			return;
		}
	}

	std::string compose(const Node& node) {
		std::string content;

		recursiveCompose(node, 0, "", content);

		return content;
	}
}
