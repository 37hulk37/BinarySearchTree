#ifndef BINARY_SEARCH_TREE_DICTIONARY_H
#define BINARY_SEARCH_TREE_DICTIONARY_H

#include <utility>
#include <ostream>
#include <string>

#include "search_tree.h"

class dictionary {
private:
    search_tree<std::string, std::vector<std::string>> tree;
    std::string pathToDict;

    void loadDictionary();

    void addNodeToDictionary(const std::string& key, const std::vector<std::string>& splittedString);

    static std::vector<std::string> split(const std::string& str, char separator);

public:
    explicit dictionary(std::string  pathToDict = "../dictionary.properties") :
            tree(), pathToDict(std::move(pathToDict)) {
        loadDictionary();
    }

    std::vector<std::string> search(const std::string& toTranslate);

    void add(const std::string& word, const std::vector<std::string>& translations);

    void remove(const std::string& key);

    friend std::ostream &operator<<(std::ostream &os, const dictionary &dictionary);
};


#endif //BINARY_SEARCH_TREE_DICTIONARY_H
