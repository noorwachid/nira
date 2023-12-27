# Nira 
YAML without unnecesary features

- No JSON subset
- No keywords
- Only 1 document in 1 file
- Only 3 data types: string, array (vector of Node), and map (unordered_map of string and Node)

#### API
~~~ cpp
Nira::Node node;
node["message"] = "success";
node["data"]["title"] = "Top 10 Best Data Interchange Format";
node["data"]["content"] = "1. JSON...";
node["data"]["tags"].add("yaml");
node["data"]["tags"].add("json");
node["data"]["tags"].add("programming");

std::cout << Nira::compose(node);
~~~

~~~ cpp
Nira::Node node = Nira::parse(R"(
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

std::cout << Nira::compose(node);
~~~
