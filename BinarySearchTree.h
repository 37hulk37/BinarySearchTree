#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <queue>

template<class T>
class BinarySearchTree {
private:
    template <class U>
    struct Node {
        U key;
        Node<U>* left;
        Node<U>* right;
        Node<U>* parent;

        Node(U k, Node<U>* l = nullptr, Node<U>* r = nullptr, Node<U>* p = nullptr) :
                key(k), left(l), right(r), parent(p) { }
    };

    Node<T>* root;
    size_t size;

    void deleteTree(Node<T>* cur);
    Node<T>*  iterativeSearchNode(const T& value) const;
    void printNode(std::ostream& out, Node<T>* cur) const;
    Node<T>* minRight(Node<T>* cur);
    size_t getSize(Node<T>* cur) const;
    size_t getHeight(Node<T>* cur) const;
    void inorderWalk(Node<T>* cur) const;

public:
    BinarySearchTree() : root(nullptr), size(0) { }
    virtual ~BinarySearchTree();

    BinarySearchTree(BinarySearchTree<T>&& src) noexcept;
    BinarySearchTree<T>& operator=(BinarySearchTree<T>&& src) noexcept;
    BinarySearchTree(BinarySearchTree<T>& src) = delete;
    BinarySearchTree<T>& operator=(BinarySearchTree<T>& src) = delete;

    bool insert(const T& value);
    bool deleteKey(const T& value);
    bool iterativeSearch(const T& value);
    void print(std::ostream& out) const;
    size_t getSize() const;
    size_t getHeight() const;
    void iterativeInorderWalk() const;
    void inorderWalk() const;
};

template<class T>
void BinarySearchTree<T>::deleteTree(Node<T> *cur) {
    if (cur) {
        deleteTree(cur->left);
        deleteTree(cur->right);
        delete cur;
    }
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree<T>() {
    deleteTree(root);
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src) noexcept {
    std::swap(root, src.root);
    std::swap(size, src.size);
    src.root = nullptr;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& src) noexcept {
    if (*this != src) {
        std::swap(root, src.root);
    }
}

template<class T>
bool BinarySearchTree<T>::insert(const T& value) {
    if ( !root ) {
        root = new Node<T>(value);
        size++;
    } else {
        Node<T>* cur = root;

        while (cur != nullptr) {
            if (value < cur->key && cur->left == nullptr) {
                cur->left = new Node<T>(value);
                cur->left->parent = cur;
                size++;
                return true;
            }

            if (value > cur->key && cur->right == nullptr) {
                cur->right = new Node<T>(value);
                cur->right->parent = cur;
                size++;
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

template<class T>
class BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& value) const {
    Node<T>* cur = root;
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

template<class T>
bool BinarySearchTree<T>::iterativeSearch(const T& value) {
    return (iterativeSearchNode(value) != nullptr);
}

template<class T>
class BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::minRight(Node<T>* cur) {
    while (cur->left != nullptr) {
        cur = cur->left;
    }
    return cur;
}

template<class T>
bool BinarySearchTree<T>::deleteKey(const T& value) {
    Node<T>* cur = iterativeSearchNode(value);
    bool fl = false;

    if (cur) {
        fl = true;

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
            Node<T>* tmp = minRight(cur->right);
            if (cur->key < root->key) {
                tmp->parent->left = nullptr;
            } else {
                tmp->parent->right = nullptr;
            }
            cur->key = tmp->key;
            delete tmp;
        }
        size--;
    }
    return fl;
}

template<class T>
void BinarySearchTree<T>::printNode(std::ostream& out, Node<T> *cur) const {
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

template<class T>
void BinarySearchTree<T>::print(std::ostream& out) const {
    out << "{ ";
    printNode(out, root);
    out << "}" << std::endl;
}

template<class T>
size_t BinarySearchTree<T>::getSize(Node<T> *cur) const {
    if (cur == nullptr) {
        return 0;
    }
    return (1 + getSize(cur->left) + getSize(cur->right));
}

template<class T>
size_t BinarySearchTree<T>::getSize() const {
    return getSize(root);
}

template<class T>
size_t BinarySearchTree<T>::getHeight(Node<T>* cur) const {
    if (cur == nullptr){
        return 0;
    }
    return (1 + std::max(getHeight(cur->left), getHeight(cur->right)));
}

template<class T>
size_t BinarySearchTree<T>::getHeight() const {
    return getHeight(root);
}

template<class T>
void BinarySearchTree<T>::iterativeInorderWalk() const {
    std::queue<Node<T>*> q;
    Node<T>* cur = root;

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

template<class T>
void BinarySearchTree<T>::inorderWalk(Node<T>* cur) const {
    if (cur) {
        std::cout << "~" << cur->key << std::endl;
        inorderWalk(cur->left);
        inorderWalk(cur->right);
    }
}

template<class T>
void BinarySearchTree<T>::inorderWalk() const {
    inorderWalk(root);
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
