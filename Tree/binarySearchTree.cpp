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

    bool _isBST2(int mn = INT_MIN, int mx = INT_MAX) {
        bool status = mn < data && data < mx;

        if (!status)
            return false;

        bool leftBST = !left || left->_isBST2(mn, data);
        if (!leftBST)
            return false;

        bool rightBST = !right || right->_isBST2(data, mx);
        return rightBST;

    }

    BinarySearchTree* minNode() {
        BinarySearchTree* cur = this;
        while (cur && cur->left)
            cur = cur->left;
        return cur;
    }

    BinarySearchTree* _deleteNode(int target, BinarySearchTree* node) {
        if (!node)
            return nullptr;

        if (target < node->data)
            node->left = _deleteNode(target, node->left);
        else if (target > node->data)
            node->right = _deleteNode(target, node->right);
        else {
            BinarySearchTree* tmp = node;

            if (!node->left && !node->right)
                node = nullptr;
            else if (!node->right)
                node = node->left;
            else if (!node->left)
                node = node->right;
            else {
                BinarySearchTree* mn = node->right->minNode();
                node->data = mn->data;
                node->right = _deleteNode(node->data, node->right);
                tmp = nullptr;
            }
            if (tmp)
                delete tmp;
        }
        return node;
    }
public:
    explicit BinarySearchTree(int const data) :
            data(data) {
    }

    BinarySearchTree(int const data, BinarySearchTree* left, BinarySearchTree* right) :
            data(data), left(left), right(right){
    }

    BinarySearchTree() = default;

    ~BinarySearchTree() {
        clear(left);
        clear(right);
    }

    void clear(BinarySearchTree *&root) {
        if(!root)
            return;
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;
    }

    void deleteNode(BinarySearchTree* node) {
        delete node->left;
        delete node->right;
    }

    void deleteValue(int target) {
        if (target == data && !left && !right)
            return; // root
        _deleteNode(target, this);
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

    int smallestKth(int &k) {
        if (k == 0)
            return -1234;
        if (left) {
            int res = left->smallestKth(k);
            if (k == 0)
                return res;
        }
        --k;
        if (k == 0)
            return data;
        if (right)
            right->smallestKth(k);
        return -1234;
    }

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

    int lowestCommonSuccessor(int x, int y) {
        if (x > data && y < data)
            return left->lowestCommonSuccessor(x, y);
        if (x > data && y > data)
            return right->lowestCommonSuccessor(x, y);
        return data;
    }

    bool isBST2() {
        return _isBST2();
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
    cout << tree.isBST2();
    return 0;
}