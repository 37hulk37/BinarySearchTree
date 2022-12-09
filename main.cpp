#include <iostream>
#include "BinarySearchTree.h"

template<class T>
void func(BinarySearchTree<T>& src) {

}

int main() {
    BinarySearchTree<double> tree;

    tree.insert(5);
    tree.insert(6);
    tree.insert(2);
    tree.insert(4);
    tree.insert(3);
    tree.insert(8);
    tree.insert(1);
    tree.insert(7);
    tree.insert(7.6);
    tree.insert(7.5);
    tree.insert(9);

    std::cout << "height = " << tree.getHeight() << std::endl;
    std::cout << "size = " << tree.getSize()<< std::endl;

    std::ostream& out = std::cout;
    tree.print(out);
    std::cout << (tree.iterativeSearch(6) ? "6 find" : "6 not find") << std::endl;
    std::cout << (tree.iterativeSearch(78) ? "78 find" : "78 not find") << std::endl;

    std::cout << (tree.deleteKey(1) ? "true" : "false") << std::endl;
    std::cout << (tree.deleteKey(34) ? "true" : "false") << std::endl;
    std::cout << (tree.deleteKey(4) ? "true" : "false") << std::endl;
    std::cout << (tree.deleteKey(8) ? "true" : "false") << std::endl;

    std::cout << "size = " << tree.getSize()<< std::endl;
    std::cout << "height = " << tree.getHeight() << std::endl;
    std::cout << "delete: ";
    tree.print(out);

    //std::cout << "recursive:" << std::endl;
    //tree.inorderWalk();
    std::cout << "iterative:" << std::endl;
    std::cout << "tree:" << std::endl;
    tree.iterativeInorderWalk();

    BinarySearchTree<double> tree2;
    tree2.insert(5);
    tree2.insert(2);
    tree2.insert(6);
    tree2.insert(3);
    tree2.insert(9);
    tree2.insert(7);
    tree2.insert(7.6);
    tree2.insert(7.5);

    std::cout << "tree2:" << std::endl;
    tree2.iterativeInorderWalk();

    tree.print(out);
    tree2.print(out);
    std::cout << (tree.equals(tree2) ? "true" : "false") << std::endl;
    tree.deleteKey(5);

    tree.print(out);
    tree2.print(out);
    std::cout << (tree.equals(tree2) ? "true" : "false") << std::endl;
    std::cout << (tree.findSame(tree2) ? "found similarities" : "no coincidences") << std::endl;

    BinarySearchTree<double> tree3;
    tree3.insert(89);

    tree2.print(out);
    tree3.print(out);
    std::cout << (tree2.findSame(tree3) ? "found similarities" : "no coincidences") << std::endl;

    BinarySearchTree<double> tree1 = std::move(tree);
    func(tree1);

    tree.print(out);
    tree2.print(out);
    std::cout << (tree3.findSame(tree1) ? "found similarities" : "no coincidences") << std::endl;

    return 0;
}
