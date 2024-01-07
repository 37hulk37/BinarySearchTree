#include "dictionary.h"

#include <fstream>
#include <sstream>
#include <format>
#include <string>

std::vector<std::basic_string<char>> dictionary::search(const std::string& toTranslate) {
    auto opt = tree.searchNode(toTranslate);

    return (opt.has_value() ? opt.value()->value :
        throw std::runtime_error(std::format("Not found translation for {}", toTranslate)));
}

void dictionary::add(const std::string& word, const std::vector<std::string>& translations) {
    const auto nodeOpt = tree.searchNode(word);
    if (nodeOpt.has_value()) {
        tree.compute(nodeOpt.value(),
                     [&translations](const auto& k, auto& v)-> std::vector<std::string> {
                         for (const auto& t: translations) {
                             v.emplace_back(t);
                         }
                         return v;
                     });
    } else {
        tree.insert(word, translations);
    }
}

void dictionary::remove(const std::string& key) {
    tree.deleteKey(key);
}

void dictionary::loadDictionary() {
    std::ifstream dictFile(pathToDict, std::ios::in);
    if ( !dictFile.is_open()) {
        throw std::runtime_error(std::format("Can not open file with name {}", pathToDict));
    }

    std::string str;
    while (std::getline(dictFile, str)) {
        auto splitted = split(str, ':');
        add(splitted[0], { splitted[1] });
    }
}

std::vector<std::string> dictionary::split(const std::string& str, char separator) {
    std::stringstream ss(str);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(ss, token, separator)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::ostream &operator<<(std::ostream& os, const dictionary& dictionary) {
    os << dictionary.tree;
    return os;
}
