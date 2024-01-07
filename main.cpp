#include "dictionary.h"

#include <iostream>

int main() {
    dictionary dict;

    std::cout << dict << std::endl;

    try {
        dict.remove("axe");
        dict.remove("123");

        dict.remove("plane");

        auto translations = dict.search("cool");
        for (const auto& val: translations) {
            std::cout << val << std::endl;
        }

        dict.search("plane");
    } catch (std::runtime_error& error) {
        std::cout << error.what() << std::endl;
    }

    dict.add("plane", std::vector<std::string> {"b777", "b787"});
    dict.add("samsung", std::vector<std::string> {"a23", "a22"});

    std::cout << dict << std::endl;

    return 0;
}
