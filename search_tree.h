#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include "queue"
#include <vector>
#include <ostream>
#include <iostream>
#include <optional>

template<class T1, class T2>
class search_tree {
private:
    template <class U1, class U2>
    struct Node {
        U1 key;
        Node<U1, U2>* left;
        Node<U1, U2>* right;
        Node<U1, U2>* parent;
        std::vector<U2> values;

        explicit Node(U1 k, Node<U1, U2>* l = nullptr, Node<U1, U2>* r = nullptr, Node<U1, U2>* p = nullptr) :
                key(k), left(l), right(r), parent(p), values(4) { };

        bool operator<(const Node<U1, U2> &rhs) const {
            return key < rhs.key;
        }
    };

    Node<T1, T2>* root;

    void deleteTree(Node<T1, T2>* cur);
    Node<T1, T2>*  iterativeSearchNode(const T1& value) const;
    void printNode(std::ostream& out, Node<T1, T2>* cur) const;
    void deleteKey(Node<T1, T2>* cur);
    Node<T1, T2>* minRight(Node<T1, T2>* cur);
    size_t getSize(Node<T1, T2>* cur) const;
    size_t getHeight(Node<T1, T2>* cur) const;
    void inorderWalk(Node<T1, T2>* cur, const Node<T1, T2>* other, size_t& numEq) const;

public:
    search_tree() : root(nullptr) { }
    virtual ~search_tree();

    search_tree(search_tree<T1, T2>&& src) noexcept;
    search_tree<T1, T2>& operator=(search_tree<T1, T2>&& src) noexcept;
    search_tree(search_tree<T1, T2>& src) = delete;
    search_tree<T1, T2>& operator=(search_tree<T1, T2>& src) = delete;

    bool insert(const T1& value);
    bool deleteKey(const T1& value);
    std::optional<std::string> iterativeSearch(const T1& value);
    void print(std::ostream& out) const;
    size_t getSize() const;
    size_t getHeight() const;
    void iterativeInorderWalk() const;
    void inorderWalk() const;

    bool equals(const search_tree<T1, T2>& other);
    bool findSame(const search_tree<T1, T2>& other);
};

template<class T1, class T2>
void search_tree<T1, T2>::deleteTree(Node<T1, T2> *cur) {
    if (cur) {
        deleteTree(cur->left);
        deleteTree(cur->right);
        delete cur;
    }
}

template<class T1, class T2>
search_tree<T1, T2>::~search_tree<T1, T2>() {
    deleteTree(root);
}

template<class T1, class T2>
search_tree<T1, T2>::search_tree(search_tree<T1, T2>&& src) noexcept {
    std::swap(root, src.root);
    src.root = nullptr;
}

template<class T1, class T2>
search_tree<T1, T2>& search_tree<T1, T2>::operator=(search_tree<T1, T2>&& src) noexcept {
    if (*this != src) {
        std::swap(root, src.root);
    }
}

template<class T1, class T2>
bool search_tree<T1, T2>::insert(const T1& value) {
    if ( !root ) {
        root = new Node<T1, T2>(value);
    } else {
        Node<T1, T2>* cur = root;

        while (cur != nullptr) {
            if (value < cur->key && cur->left == nullptr) {
                cur->left = new Node<T1, T2>(value);
                cur->left->parent = cur;
                return true;
            }

            if (value > cur->key && cur->right == nullptr) {
                cur->right = new Node<T1, T2>(value);
                cur->right->parent = cur;
                return true;
            }

            if (value < cur->key) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
    }
    return false;
}

template<class T1, class T2>
class search_tree<T1, T2>::Node<T1, T2>* search_tree<T1, T2>::iterativeSearchNode(const T1& value) const {
    Node<T1, T2>* cur = root;
    if (cur) {
        while (cur && cur->key != value) {
            if (value < cur->key) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
    }
    return cur;
}

template<class T1, class T2>
std::optional<std::string> search_tree<T1, T2>::iterativeSearch(const T1& value) {
    auto node = iterativeSearchNode(value);
    return node ? std::optional{node} : std::nullopt;
}

template<class T1, class T2>
class search_tree<T1, T2>::Node<T1, T2>* search_tree<T1, T2>::minRight(Node<T1, T2>* cur) {
    while (cur->left != nullptr) {
        cur = cur->left;
    }
    return cur;
}

template<class T1, class T2>
bool search_tree<T1, T2>::deleteKey(const T1 &value) {
    Node<T1, T2>* cur = iterativeSearchNode(value);
    bool fl = false;

    if (cur) {
        fl = true;
        deleteKey(cur);
    }
    return fl;
}

template<class T1, class T2>
void search_tree<T1, T2>::deleteKey(Node<T1, T2>* cur) {
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
        Node<T1, T2>* tmp = minRight(cur->right);
        T1 replaceValue = tmp->key;
        deleteKey(tmp);
        cur->key = replaceValue;
    }
}

template<class T1, class T2>
void search_tree<T1, T2>::printNode(std::ostream& out, Node<T1, T2> *cur) const {
    if (cur) {
        if (cur->left) {
            printNode(out, cur->left);
        }
        out << cur->key << " ";
        if (cur->right) {
            printNode(out, cur->right);
        }
    }
}

template<class T1, class T2>
void search_tree<T1, T2>::print(std::ostream& out) const {
    out << "{ ";
    printNode(out, root);
    out << "}" << std::endl;
}

template<class T1, class T2>
size_t search_tree<T1, T2>::getSize(Node<T1, T2> *cur) const {
    if (cur == nullptr) {
        return 0;
    }
    return (1 + getSize(cur->left) + getSize(cur->right));
}

template<class T1, class T2>
size_t search_tree<T1, T2>::getSize() const {
    return getSize(root);
}

template<class T1, class T2>
size_t search_tree<T1, T2>::getHeight(Node<T1, T2>* cur) const {
    if (cur == nullptr) {
        return 0;
    }
    return (1 + std::max(getHeight(cur->left), getHeight(cur->right)));
}

template<class T1, class T2>
size_t search_tree<T1, T2>::getHeight() const {
    return getHeight(root);
}

template<class T1, class T2>
void search_tree<T1, T2>::iterativeInorderWalk() const {
    std::queue<Node<T1, T2>*> q;
    Node<T1, T2>* cur = root;

    q.push(cur);

    while ( !q.empty() ) {
        cur = q.front();
        q.pop();
        if (cur->left) {
            q.push(cur->left);
        }
        if (cur->right) {
            q.push(cur->right);
        }
        std::cout << "@" << cur->key << std::endl;
    }
}

//template<class T1, class T2>
//void search_tree<T1, T2>::inorderWalk(Node<T1, T2>* cur) const {
//    if (cur) {
//        std::cout << "~" << cur->key << std::endl;
//        inorderWalk(cur->left);
//        inorderWalk(cur->right);
//    }
//}

template<class T1, class T2>
void search_tree<T1, T2>::inorderWalk() const {
    inorderWalk(root);
}

template<class T1, class T2>
void search_tree<T1, T2>::inorderWalk(Node<T1, T2>* cur, const Node<T1, T2>* other, size_t& numEq) const {
    if (cur && other) {
        if (cur->key == other->key) {
            numEq++;
        }

        inorderWalk(cur->left, other->left, numEq);
        inorderWalk(cur->right, other->right, numEq);
    }
}

template<class T1, class T2>
bool search_tree<T1, T2>::equals(const search_tree<T1, T2>& other) {
    size_t numEq = 0;

    if (root->key == other.root->key) {
        inorderWalk(root, other.root, numEq);
    }

    return numEq == getSize();
}

template<class T1, class T2>
bool search_tree<T1, T2>::findSame(const search_tree<T1, T2> &other) {
    size_t numEq = 0;

    if (root) {
        inorderWalk(root, other.root, numEq);
    }

    return numEq > 0;
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
