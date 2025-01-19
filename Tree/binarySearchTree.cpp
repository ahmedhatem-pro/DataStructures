#include <iostream>
#include <vector>
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

    void findParentsChain(vector<BinarySearchTree*> &parent, const int target) {
        if (data == target)
            return;
        parent.push_back(this);
        if (target < data && left)
            left->findParentsChain(parent, target);
        else if (right)
            right->findParentsChain(parent, target);
    }

    BinarySearchTree* _successor(const int target) {
        vector<BinarySearchTree*> parents;
        findParentsChain(parents, target);
        for (int i = static_cast<int>(parents.size()) - 1; i >= 0; i--) {
            if (parents[i]->data > target)
                return parents[i];
        }
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

    BinarySearchTree* successor(int target) {
        BinarySearchTree* node = searchNode(target);
        if (node->right)
            return _minimum(node->right);
        return _successor(target);
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

    printData(tree.successor(45));
    cout << "\nBye";
    return 0;
}