#include "Nira/Lexer.h"
#include "Nira/Parse.h"
#include "Nira/Compose.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
	Nira::Node node;
	node["message"] = "success";
	node["data"]["title"] = "Top 10 Best Data Interchange Format";
	node["data"]["content"] = "1. JSON...";

	std::cout << Nira::Compose(node);

	std::cout << Nira::Compose(Nira::Parse(R"(
id: 123
detail:
  name: re2
  version:
    major: 6
    minor: 0
  publisher: macrohard
updated_at: 2023-10-23
sources:
  - one.cpp
  - two.cpp
  - three.cpp
)"));

	return 0;
}
