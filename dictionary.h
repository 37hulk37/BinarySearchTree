#ifndef BINARY_SEARCH_TREE_DICTIONARY_H
#define BINARY_SEARCH_TREE_DICTIONARY_H

#include <utility>

#include "search_tree.h"

class dictionary {
private:
    search_tree<std::string, std::string> dict;
    std::string pathToDict;

    void loadDictionary();

    void addNodeToDictionary(const std::vector<std::string>& splittedString);

    static std::vector<std::string> split(const std::string& str, char separator);

public:
    explicit dictionary(std::string  pathToDict = "../dictionary.properties") :
        dict(), pathToDict(std::move(pathToDict)) {}

    void translate();

    void add(const std::string& key, const std::vector<std::string>& translations);

    void remove(const std::string& key);
};


#endif //BINARY_SEARCH_TREE_DICTIONARY_H
