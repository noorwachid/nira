cmake_minimum_required(VERSION 3.11)

project("nira")

set(CMAKE_CXX_STANDARD 17)

add_library("nira" SHARED
	"source/Nira/Internal/Lexer.cpp"
	"source/Nira/Node.cpp"
	"source/Nira/parse.cpp"
	"source/Nira/compose.cpp"
)

target_include_directories("nira" PUBLIC "source")

