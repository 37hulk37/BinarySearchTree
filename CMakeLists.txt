cmake_minimum_required(VERSION 3.16)
project(binary-search-tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(binary-search-tree main.cpp
        search_tree.h
        dictionary.cpp
        dictionary.h
        tree_node.h
)
