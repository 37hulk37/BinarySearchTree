#ifndef BINARY_SEARCH_TREE_TREE_NODE_H
#define BINARY_SEARCH_TREE_TREE_NODE_H

#include <vector>
#include <string>

template <class K, class V>
class tree_node {
public:
    K key;
    V value;
    tree_node<K, V>* left;
    tree_node<K, V>* right;
    tree_node<K, V>* parent;

    explicit tree_node(
            K k,
            V v,
            tree_node<K, V>* l = nullptr,
            tree_node<K, V>* r = nullptr,
            tree_node<K, V>* p = nullptr
   ) : key(k), left(l), right(r), parent(p), value(v) { }

    bool operator<(const tree_node<K, V> &rhs) const {
        return key < rhs.key;
    }

    template <class K1, class V1>
    friend std::ostream &operator<<(std::ostream &os, const tree_node<K1, V1>& treeNode);
};

template <class K, class V>
std::ostream &operator<<(std::ostream &os, const tree_node<K, V>& node) {
    os << "{" << node.key << ": " << node.value << "};";
    return os;
}

template <class K, class V2>
std::ostream &operator<<(std::ostream &os, const tree_node<K, std::vector<V2>>& node) {
    os << "\n" << node.key << ": [ ";
    for (auto v: node.value) {
        os << v << ", ";
    }
    os << "]";
    return os;
}


#endif //BINARY_SEARCH_TREE_TREE_NODE_H
