#include "dictionary.h"

#include <fstream>
#include <sstream>
#include <format>
#include <string>

std::vector<std::basic_string<char>> dictionary::search(const std::string &toTranslate) {
    auto opt = tree.iterativeSearch(toTranslate);

    return (opt.has_value() ? opt.value()->value :
        throw std::runtime_error(std::format("Not found translation for {}", toTranslate)));
}

void dictionary::add(const std::string &word, const std::vector<std::string>& translations) {
    addNodeToDictionary(word, translations);
}

void dictionary::remove(const std::string &key) {
    tree.deleteKey(key);
}

void dictionary::loadDictionary() {
    std::ifstream dictFile(pathToDict, std::ios::in);
    if ( !dictFile.is_open()) {
        return;
    }

    std::string str;
    while (std::getline(dictFile, str)) {
        auto splitted = split(str, ':');
        addNodeToDictionary(splitted[0], { splitted[1] });
    }
}

void dictionary::addNodeToDictionary(const std::string& word, const std::vector<std::string>& translations) {
    auto opt = tree.iterativeSearch(word);
    if (opt.has_value()) {
        tree.compute(word,[&translations] (
                const auto& k,
                std::vector<std::string>& v
        ) -> std::vector<std::string> {
            for (const auto& t: translations) {
                v.emplace_back(t);
            }
            return v;
        });
    } else {
        tree.insert(word, translations);
    }
}

std::vector<std::string> dictionary::split(const std::string &str, char separator) {
    std::stringstream ss(str);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(ss, token, separator)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::ostream &operator<<(std::ostream &os, const dictionary &dictionary) {
    os << dictionary.tree;
    return os;
}
