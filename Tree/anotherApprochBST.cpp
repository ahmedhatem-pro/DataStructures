#include <iostream>
using namespace std;

class BST {
    int data {};
    BST *left {};
    BST *right {};
    BST *parent {};

public:
    explicit BST (const int data, BST *parent = nullptr) : data (data), parent(parent) {
    }

    void print_inorder() {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }

    void insert(const int target) {
        if (target < data) {
            if (!left) {
                left = new BST(target, this);
            }
            else
                left->insert(target);
        }   else if (target > data) {
            if(!right) {
                right = new BST(target, this);
            }
            else
                right->insert(target);
        }
    }

    BST* searchNode(const int target) {
        if (!this)
            return nullptr;

        if (target == data)
            return this;

        if (target < data)
            return left->searchNode(target);

        return right->searchNode(target);
    }

    static int _minimum(const BST *subTree) {
        if (subTree->left)
            return _minimum(subTree->left);
        return subTree->data;
    }

    int successor(const int target) {
        BST* node = searchNode(target);
        if (node->right)
            return _minimum(node->right);
        BST* parent = node->parent;
        while (parent && parent->right == node) {
            node = parent;
            parent = node->parent;
        }
        if (parent)
            return parent->data;
        return -1234;
    }
};

int main() {
    BST tree(50);
    tree.insert(20);
    tree.insert(45);
    tree.insert(70);
    tree.insert(73);
    tree.insert(35);
    tree.insert(15);
    tree.insert(60);
    cout << tree.successor(45);

    return 0;
}