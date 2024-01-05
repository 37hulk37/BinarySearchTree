#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include "tree_node.h"

#include <functional>
#include <queue>
#include <vector>
#include <ostream>
#include <iostream>
#include <optional>
#include <string>

template<class K, class V>
class search_tree {
private:
    tree_node<K, V>* root;

    void deleteTree(tree_node<K, V>* cur);
    tree_node<K, V>*  iterativeSearchNode(const K& value) const;
    void deleteKey(tree_node<K, V>* cur);
    tree_node<K, V>* minRight(tree_node<K, V>* cur);
    size_t getSize(tree_node<K, V>* cur) const;
    size_t getHeight(tree_node<K, V>* cur) const;

public:
    search_tree() : root(nullptr) { }
    virtual ~search_tree();

    search_tree(search_tree<K, V>&& src) noexcept;
    search_tree<K, V>& operator=(search_tree<K, V>&& src) noexcept;
    search_tree(search_tree<K, V>& src) = delete;
    search_tree<K, V>& operator=(search_tree<K, V>& src) = delete;

    void insert(const K& key, const V& v);
    bool deleteKey(const K& value);
    std::optional<tree_node<K, V>*> iterativeSearch(const K& value);
    size_t getSize() const;
    size_t getHeight() const;

    template <class K1, class V1>
    friend std::ostream &operator<<(std::ostream &os, const search_tree<K1, V1> &tree);

    V compute(const K& key, const std::function<V(const K&, V&)>& function);
};

template<class K, class V>
search_tree<K, V>::~search_tree() {
    deleteTree(root);
}

template<class K, class V>
void search_tree<K, V>::deleteTree(tree_node<K, V> *cur) {
    if (cur) {
        deleteTree(cur->left);
        deleteTree(cur->right);
        delete cur;
    }
}

template<class K, class V>
search_tree<K, V>::search_tree(search_tree<K, V>&& src) noexcept {
    std::swap(root, src.root);
    src.root = nullptr;
}

template<class K, class V>
search_tree<K, V>& search_tree<K, V>::operator=(search_tree<K, V>&& src) noexcept {
    if (*this != src) {
        std::swap(root, src.root);
    }
}

template<class K, class V>
void search_tree<K, V>::insert(const K& key, const V& v) {
    if ( !root ) {
        root = new tree_node<K, V>(key, v);
        return;
    }
    tree_node<K, V> *cur = root;

    while (cur != nullptr) {
        if (key < cur->key && cur->left == nullptr) {
            cur->left = new tree_node<K, V>(key, v);
            cur->left->parent = cur;
            return;
        }

        if (key > cur->key && cur->right == nullptr) {
            cur->right = new tree_node<K, V>(key, v);
            cur->right->parent = cur;
            return;
        }

        if (key < cur->key) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
}

template<class K, class V>
class tree_node<K, V>* search_tree<K, V>::iterativeSearchNode(const K& value) const {
    tree_node<K, V>* cur = root;
    if (!cur) {
        return cur;
    }
    while (cur && cur->key != value) {
        if (value < cur->key) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return cur;
}

template<class K, class V>
std::optional<tree_node<K, V>*> search_tree<K, V>::iterativeSearch(const K& value) {
    auto node = iterativeSearchNode(value);
    return (node != nullptr ? std::optional{ node } : std::nullopt);
}

template<class K, class V>
class tree_node<K, V>* search_tree<K, V>::minRight(tree_node<K, V>* cur) {
    while (cur->left != nullptr) {
        cur = cur->left;
    }
    return cur;
}

template<class K, class V>
bool search_tree<K, V>::deleteKey(const K &value) {
    tree_node<K, V>* cur = iterativeSearchNode(value);
    bool fl = false;

    if (cur) {
        fl = true;
        deleteKey(cur);
    }
    return fl;
}

template<class K, class V>
void search_tree<K, V>::deleteKey(tree_node<K, V>* cur) {
    if (cur->left == nullptr && cur->right == nullptr) {
        if (cur->key < cur->parent->key) {
            cur->parent->left = nullptr;
        } else {
            cur->parent->right = nullptr;
        }
        delete cur;
    } else if (cur->left == nullptr || cur->right == nullptr) {
        if (cur->left == nullptr) {
            cur->right->parent = cur->parent;

            if (cur->key < cur->parent->key) {
                cur->parent->left = cur->right;
            } else {
                cur->parent->right = cur->right;
            }
        } else {
            cur->left->parent = cur->parent;

            if (cur->key < cur->parent->key) {
                cur->parent->left = cur->left;
            } else {
                cur->parent->right = cur->left;
            }
        }
        delete cur;
    } else {
        tree_node<K, V>* tmp = minRight(cur->right);
        K replaceValue = tmp->key;
        deleteKey(tmp);
        cur->key = replaceValue;
    }
}

template<class K, class V>
size_t search_tree<K, V>::getSize(tree_node<K, V> *cur) const {
    if (cur == nullptr) {
        return 0;
    }
    return (1 + getSize(cur->left) + getSize(cur->right));
}

template<class K, class V>
size_t search_tree<K, V>::getSize() const {
    return getSize(root);
}

template<class K, class V>
size_t search_tree<K, V>::getHeight(tree_node<K, V>* cur) const {
    if (cur == nullptr) {
        return 0;
    }
    return (1 + std::max(getHeight(cur->left), getHeight(cur->right)));
}

template<class K, class V>
size_t search_tree<K, V>::getHeight() const {
    return getHeight(root);
}

template<class K, class V>
V search_tree<K, V>::compute(const K &key, const std::function<V(const K&, V&)>& function) {
    auto node = iterativeSearchNode(key);
    return std::apply(function, std::forward_as_tuple(node->key, node->value));
}

template<class K, class V>
std::ostream &operator<<(std::ostream &os, const search_tree<K, V> &tree) {
    std::queue< tree_node<K, V>* > q;
    auto* cur = tree.root;
    q.push(cur);

    while ( !q.empty()) {
        cur = q.front();
        q.pop();
        if (cur->left) {
            q.push(cur->left);
        }
        if (cur->right) {
            q.push(cur->right);
        }
        std::cout << *cur << std::endl;
    }
    return os;
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
