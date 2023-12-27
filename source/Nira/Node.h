#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace Nira {
	class Node {
	public:
		Node();

		Node(const std::string& value);

		Node(const std::vector<Node>& value);

		Node(const std::unordered_map<std::string, Node>& value);

		Node& operator=(const std::string& value);

		Node& operator=(const std::vector<Node>& value);

		Node& operator=(const std::unordered_map<std::string, Node>& value);

		void add(const Node& node);

		void add(const std::string& value);

		void add(const std::vector<Node>& value);

		void add(const std::unordered_map<std::string, Node>& value);

		size_t size() const;

		Node& operator[](size_t index);

		const Node& operator[](size_t index) const;

		bool hasKey(const std::string& key) const;

		Node& operator[](const std::string& key);

		const Node& operator[](const std::string& key) const;

		bool isString() const;

		bool isArray() const;

		bool isMap() const;

		const std::string& asString() const;

		const std::vector<Node>& asArray() const;

		const std::unordered_map<std::string, Node>& asMap() const;

	private:
		std::variant<std::string, std::vector<Node>, std::unordered_map<std::string, Node>> _value;
	};
}
