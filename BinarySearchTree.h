#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

template<class T>
class BinarySearchTree {
private:
    template<class U>
    struct Node {
        U key;
        Node<U>* left;
        Node<U>* right;
        Node<U>* parent;

        Node<U>(U k, Node<U>* l = nullptr, Node<U>* r = nullptr, Node<U>* p = nullptr) :
                key(k), left(l), right(r), parent(p) { }
    };

    Node<T>* root;


    Node<T>* iterativeSearchNode(const T& key) const;
    void printNode(std::ostream& out, Node<T>* root) const;
    int getCount(const Node<T>* node) const;
    int getHeight(const Node<T>* node) const;
    void inorderWalk(Node<T>* node) const;

public:
    BinarySearchTree() : root(nullptr) { }
    virtual ~BinarySearchTree();

    BinarySearchTree(BinarySearchTree<T>&& src);
    BinarySearchTree<T>& operator=(BinarySearchTree<T>&& src);
    BinarySearchTree(BinarySearchTree<T>& src) = delete;
    BinarySearchTree<T>& operator=(BinarySearchTree<T>& src) = delete;

    bool insert(const T& key);
    bool deleteKey(const T& key);
    void print(std::ostream& out) const;
    int getHeight() const;
    void iterativeInorderWalk() const;
    void inorderWalk() const;
};

template<class T>
BinarySearchTree<T>::~BinarySearchTree<T>() {

}

template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src) {
    std::swap(root, src.root);
    src.root = nullptr;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& src) {
    if (*this != src) {
        std::swap(root, src.root);
    }
}

template<class T>
bool insert(const T& key) {

}


#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
