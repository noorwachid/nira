#pragma once

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>

namespace Nira
{
	class Node
	{
	public:
		Node();

		Node(const std::string& value);

		Node(const std::vector<Node>& value);

		Node(const std::unordered_map<std::string, Node>& value);

		Node& operator=(const std::string& value);

		Node& operator=(const std::vector<Node>& value);

		Node& operator=(const std::unordered_map<std::string, Node>& value);

		void Add(const Node& node);

		void Add(const std::string& value);

		void Add(const std::vector<Node>& value);

		void Add(const std::unordered_map<std::string, Node>& value);

		size_t Size() const;

		Node& operator[](size_t index);

		const Node& operator[](size_t index) const;

		bool HasKey(const std::string& key) const;

		Node& operator[](const std::string& key);

		const Node& operator[](const std::string& key) const;

		bool IsString() const;

		bool IsList() const;

		bool IsDictionary() const;

		const std::string& AsString() const;

		const std::vector<Node>& AsList() const;

		const std::unordered_map<std::string, Node>& AsDictionary() const;

	private:
		std::variant<std::string, std::vector<Node>, std::unordered_map<std::string, Node>> _value;
	};
}
