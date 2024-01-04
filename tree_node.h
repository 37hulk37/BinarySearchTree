#ifndef BINARY_SEARCH_TREE_TREE_NODE_H
#define BINARY_SEARCH_TREE_TREE_NODE_H

#include <vector>

template <class U1, class U2>
class tree_node {
    U1 key;
    tree_node<U1, U2>* left;
    tree_node<U1, U2>* right;
    tree_node<U1, U2>* parent;
    std::vector<U2> values;

    explicit tree_node(U1 k, tree_node<U1, U2>* l = nullptr, tree_node<U1, U2>* r = nullptr, tree_node<U1, U2>* p = nullptr) :
            key(k), left(l), right(r), parent(p), values(4) { };

    bool operator<(const tree_node<U1, U2> &rhs) const {
        return key < rhs.key;
    }
};


#endif //BINARY_SEARCH_TREE_TREE_NODE_H
