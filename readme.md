# Nira 
YAML without unnecesary features

- No JSON subset
- No keywords
- Only 1 document in 1 file
- Only 3 data types: string, list (vector of Node), and dictionary (unordered_map of string and Node)

#### API
~~~ cpp
Nira::Node node;
node["message"] = "success";
node["data"]["title"] = "Top 10 Best Data Interchange Format";
node["data"]["content"] = "1. JSON...";

std::cout << Nira::Compose(node);
~~~

~~~ cpp
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
~~~
