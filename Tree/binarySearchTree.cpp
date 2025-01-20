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
        return nullptr;
    }
public:
    explicit BinarySearchTree(int const data) :
            data(data) {
    }

    BinarySearchTree(int const data, BinarySearchTree* left, BinarySearchTree* right) :
            data(data), left(left), right(right){
    }

    BinarySearchTree() = default;

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

    BinarySearchTree* successor(const int target) {
        if (const BinarySearchTree* node = searchNode(target); node->right)
            return _minimum(node->right);
        return _successor(target);
    }

    bool searchIterative(const int target) {
        const BinarySearchTree* curr = this;
        while (curr) {
            if (data == target)
                return true;
            if (target == curr->data)
                return true;
            if (target < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return false;
    }

    void getInorderVector(vector<int>& values) {
        if (left)
            left->getInorderVector(values);

        values.push_back(data);

        if (right)
            right->getInorderVector(values);
    }

    bool isBST() {
        vector<int> values;
        getInorderVector(values);

        for (int i = 1; i < static_cast<int> (values.size()); i++) {
            if (values[i] <= values[i - 1])
                return false;
        }
        return true;
    }

    int smallestKth(const int k, int count = 1) {
        if (left) {
            left->smallestKth(k, count);
        }
        if (count == k)
            return data;
        count++;
        if (right)
            right->smallestKth(k, count);

        return -1234;
    }

    friend  void printData(const BinarySearchTree* tree);

    static BinarySearchTree* _buildBalancedBST(vector<int> &values, int start = 0, int end = -10) {
        if (end == -10)
            end = static_cast<int> (values.size())- 1;
        if (start > end)
            return nullptr;

        int mid = (start + end) / 2;
        BinarySearchTree *left = _buildBalancedBST(values, start, mid - 1);
        BinarySearchTree *right = _buildBalancedBST(values, mid + 1, end);
         // Memory leak here Hopefully it can be solved by implementing a destructor

        return new BinarySearchTree(values[mid], left, right);
    }

    void buildBalancedBST(vector<int> &values) {
        const BinarySearchTree* temp = _buildBalancedBST(values);
        *this = *temp;
    }
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
    vector v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    BinarySearchTree tree2;
    tree2.buildBalancedBST(v);
    tree2.print_inorder();
    return 0;
}