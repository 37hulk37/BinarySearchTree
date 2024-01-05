#include "dictionary.h"

#include <iostream>

void handleExceptionIfThrown(const std::function<void()>& function) {
    try {
        function();
    } catch (std::runtime_error& error) {
        std::cout << error.what() << std::endl;
    }
}

int main() {
    dictionary dict;

    std::cout << dict << std::endl;

    handleExceptionIfThrown([&dict]() {
        dict.remove("axe");
        dict.remove("123");
    });

    handleExceptionIfThrown([&dict]() {
        dict.add("plane", std::vector<std::string> {"b777", "b787"});
        dict.add("samsung", std::vector<std::string> {"a23", "a22"});
    });

    handleExceptionIfThrown([&dict]() {
        dict.remove("plane");
    });

    handleExceptionIfThrown([&dict]() {
        auto translations = dict.search("cool");
        for (const auto& val: translations) {
            std::cout << val << std::endl;
        }
    });

    std::cout << dict << std::endl;

    return 0;
}
