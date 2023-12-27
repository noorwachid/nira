#include "Nira/Node.h"

namespace Nira {
	Node::Node() {
	}

	Node::Node(const std::string& value) {
		_value = value;
	}

	Node::Node(const std::vector<Node>& value) {
		_value = value;
	}

	Node::Node(const std::unordered_map<std::string, Node>& value) {
		_value = value;
	}

	Node& Node::operator=(const std::string& value) {
		_value = value;
		return *this;
	}

	Node& Node::operator=(const std::vector<Node>& value) {
		_value = value;
		return *this;
	}

	Node& Node::operator=(const std::unordered_map<std::string, Node>& value) {
		_value = value;
		return *this;
	}

	void Node::add(const Node& node) {
		if (!isArray())
			_value = std::vector<Node>();

		std::get<std::vector<Node>>(_value).push_back(node);
	}

	void Node::add(const std::string& value) {
		add(Node(value));
	}

	void Node::add(const std::vector<Node>& value) {
		add(Node(value));
	}

	void Node::add(const std::unordered_map<std::string, Node>& value) {
		add(Node(value));
	}

	size_t Node::size() const {
		if (!isArray())
			return 0;

		return std::get<std::vector<Node>>(_value).size();
	}

	Node& Node::operator[](size_t index) {
		if (!isArray())
			_value = std::vector<Node>();

		return std::get<std::vector<Node>>(_value)[index];
	}

	const Node& Node::operator[](size_t index) const {
		return std::get<std::vector<Node>>(_value)[index];
	}

	bool Node::hasKey(const std::string& key) const {
		if (!isMap())
			return false;

		return std::get<std::unordered_map<std::string, Node>>(_value).count(key);
	}

	Node& Node::operator[](const std::string& key) {
		if (!isMap())
			_value = std::unordered_map<std::string, Node>();

		return std::get<std::unordered_map<std::string, Node>>(_value)[key];
	}

	const Node& Node::operator[](const std::string& key) const {
		return std::get<std::unordered_map<std::string, Node>>(_value).at(key);
	}

	bool Node::isString() const {
		return std::holds_alternative<std::string>(_value);
	}

	bool Node::isArray() const {
		return std::holds_alternative<std::vector<Node>>(_value);
	}

	bool Node::isMap() const {
		return std::holds_alternative<std::unordered_map<std::string, Node>>(_value);
	}

	const std::string& Node::asString() const {
		return std::get<std::string>(_value);
	}

	const std::vector<Node>& Node::asArray() const {
		return std::get<std::vector<Node>>(_value);
	}

	const std::unordered_map<std::string, Node>& Node::asMap() const {
		return std::get<std::unordered_map<std::string, Node>>(_value);
	}
}
