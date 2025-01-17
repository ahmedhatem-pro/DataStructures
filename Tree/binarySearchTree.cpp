#include <iostream>
using namespace std;

class BinarySearchTree {
    int data { };
    BinarySearchTree* left { };
    BinarySearchTree* right { };

    BinarySearchTree* searchNode(const int target) {
        if (!this)
            return nullptr;

        if (target == data)
            return this;

        if (target < data)
             return left->searchNode(target);

        return right->searchNode(target);
    }

    static BinarySearchTree* _minimum(BinarySearchTree *subTree) {
        if (subTree->left)
            return _minimum(subTree->left);
        return subTree;
    }
public:
    explicit BinarySearchTree(int const data) :
            data(data) {
    }

    void print_inorder() {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }

    bool search(int const target) {
        if (target == data)
            return true;

        if (target < data)
            return left && left->search(target);

        return right && right->search(target);
    }

    void insert(int const target) {
        if (target < data) {
            if (!left)
                left = new BinarySearchTree(target);
            else
                left->insert(target);
        }   else if (target > data) {
            if(!right)
                right = new BinarySearchTree(target);
            else
                right->insert(target);
        }   // else : already exists

    }

    BinarySearchTree* minimum(const int target) {
        BinarySearchTree *subTree = searchNode(target);
        if (subTree == nullptr)
            return nullptr;
        return _minimum(subTree);
    }

    friend  void printData(const BinarySearchTree* tree);
};

void printData(const BinarySearchTree* tree) {
    if (tree == nullptr)
        cout << "There is no node with this value!";
    else
        cout << tree->data;
}


int main() {
    BinarySearchTree tree(50);
    tree.insert(20);
    tree.insert(45);
    tree.insert(70);
    tree.insert(73);
    tree.insert(35);
    tree.insert(15);
    tree.insert(60);

    cout << "bye";

    return 0;
}