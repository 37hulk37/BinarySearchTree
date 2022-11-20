#include <iostream>
#include "BinarySearchtree.h"

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
    tree.insert(7.7);
    tree.insert(9);
    
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
    std::cout << "delete: ";
    tree.print(out);

    return 0;
}
