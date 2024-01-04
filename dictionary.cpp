#include "dictionary.h"

#include <fstream>
#include <sstream>

void dictionary::translate() {

}

void dictionary::add(const std::string &key, const std::vector<std::string> &translations) {

}

void dictionary::remove(const std::string &key) {

}

void dictionary::loadDictionary() {
    std::ifstream dictFile(pathToDict, std::ios::in);

    while ( !dictFile.eof()) {
        std::string str;
        dictFile >> str;

        addNodeToDictionary(split(str, ':'));
    }
}

void dictionary::addNodeToDictionary(const std::vector<std::string> &splittedString) {
    std::string key = splittedString[0];

    dict.iterativeSearch(key);
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
