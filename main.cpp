#include "dictionary.h"

#include <iostream>

int main() {
    dictionary dict;

    std::cout << dict << std::endl;

    dict.remove("axe");

    dict.add("cs", std::vector<std::string> {"23", "34"});

    auto translations = dict.search("plane");

    for (const auto& val: translations) {
        std::cout << val << std::endl;
    }

    std::cout << dict << std::endl;

    return 0;
}
