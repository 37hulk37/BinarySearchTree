#include "dictionary.h"

#include <iostream>

int main() {
    dictionary dict;

    std::cout << dict << std::endl;

    dict.remove("axe");

    dict.add("plane", std::vector<std::string> {"b777", "b787"});
    dict.add("samsung", std::vector<std::string> {"a23", "a22"});

    auto translations = dict.search("plane");

    for (const auto& val: translations) {
        std::cout << val << std::endl;
    }

    std::cout << dict << std::endl;

    return 0;
}
