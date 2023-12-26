#include "Nira/Node.h"

namespace Nira
{
	Node::Node()
	{
	}

	Node::Node(const std::string& value)
	{
		_value = value;
	}

	Node::Node(const std::vector<Node>& value)
	{
		_value = value;
	}

	Node::Node(const std::unordered_map<std::string, Node>& value)
	{
		_value = value;
	}

	Node& Node::operator=(const std::string& value)
	{
		_value = value;
		return *this;
	}

	Node& Node::operator=(const std::vector<Node>& value)
	{
		_value = value;
		return *this;
	}

	Node& Node::operator=(const std::unordered_map<std::string, Node>& value)
	{
		_value = value;
		return *this;
	}

	void Node::Add(const Node& node)
	{
		if (!IsList())
			_value = std::vector<Node>();

		std::get<std::vector<Node>>(_value).push_back(node);
	}

	void Node::Add(const std::string& value)
	{
		Add(Node(value));
	}

	void Node::Add(const std::vector<Node>& value)
	{
		Add(Node(value));
	}

	void Node::Add(const std::unordered_map<std::string, Node>& value)
	{
		Add(Node(value));
	}

	size_t Node::Size() const
	{
		if (!IsList())
			return 0;

		return std::get<std::vector<Node>>(_value).size();
	}

	Node& Node::operator[](size_t index)
	{
		if (!IsList())
			_value = std::vector<Node>();

		return std::get<std::vector<Node>>(_value)[index];
	}

	const Node& Node::operator[](size_t index) const
	{
		return std::get<std::vector<Node>>(_value)[index];
	}

	bool Node::HasKey(const std::string& key) const
	{
		if (!IsDictionary())
			return false;

		return std::get<std::unordered_map<std::string, Node>>(_value).count(key);
	}

	Node& Node::operator[](const std::string& key)
	{
		if (!IsDictionary())
			_value = std::unordered_map<std::string, Node>();

		return std::get<std::unordered_map<std::string, Node>>(_value)[key];
	}

	const Node& Node::operator[](const std::string& key) const
	{
		return std::get<std::unordered_map<std::string, Node>>(_value).at(key);
	}

	bool Node::IsString() const
	{
		return std::holds_alternative<std::string>(_value);
	}

	bool Node::IsList() const
	{
		return std::holds_alternative<std::vector<Node>>(_value);
	}

	bool Node::IsDictionary() const
	{
		return std::holds_alternative<std::unordered_map<std::string, Node>>(_value);
	}

	const std::string& Node::AsString() const
	{
		return std::get<std::string>(_value);
	}

	const std::vector<Node>& Node::AsList() const
	{
		return std::get<std::vector<Node>>(_value);
	}

	const std::unordered_map<std::string, Node>& Node::AsDictionary() const
	{
		return std::get<std::unordered_map<std::string, Node>>(_value);
	}
}
