#include <iostream>
#include <deque>
#include <queue>
#include <stack>
#include <vector>
using namespace std;


vector<int> nextGreaterIndex(deque<int> v) {
    stack<int> pos;
    vector<int> ans(static_cast<int>(v.size()));

    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        while (!pos.empty() && v[i] > v[pos.top()]) {
            v[pos.top()] = i;
            pos.pop();
        }
        pos.push(i);
    }

    while (!pos.empty()) {
        v[pos.top()] = v.size();
        pos.pop();
    }

    for (int i = 0; i < static_cast<int>(v.size()); i++)
        ans[i] = v[i];
    return ans;
}

class BST {
    int data {};
    BST *left {};
    BST *right {};
    BST *parent {};

public:
    explicit BST (const int data, BST *parent = nullptr) : data (data), parent(parent) {
    }

    // BST(deque<int> &preOrder, const vector<int> &nextGreater, int start = 0, int end = -10) {
    //     if (end == -10)
    //         end = static_cast<int> (preOrder.size()) - 1;
    //
    //     data = preOrder[start];
    //
    //     int split = nextGreater[start];
    //
    //     if (split > end)
    //         split = end + 1;
    //
    //     if (start + 1 <= split - 1)
    //         left = new BST (preOrder, nextGreater, start + 1, split - 1);
    //     if (split <= end)
    //         right = new BST (preOrder, nextGreater, split, end);
    // }
    // BST (deque<int> &preOrder) : BST (preOrder, nextGreaterIndex(preOrder)) {
    // }
    //
    // BST (deque<int> &preOrder, int start = 0, int end = -10) { O(n^2)
    //     if (end == -10)
    //     end = static_cast<int> (preOrder.size()) - 1;
    //     data = preOrder[start];
    //
    //     for (int split = start + 1; split <= end + 1; split++){
    //         if (split == end + 1 || preOrder[split] > data) {
    //             if (start + 1 <= split - 1)
    //                 left = new BST (preOrder, start + 1, split - 1);
    //             if (split <= end)
    //                 right = new BST (preOrder, split, end);
    //             break;
    //         }
    //     }
    // }

    // BST (deque<int> &preOrder, int min = 0, int max = 1001) {
    //     data = preOrder[0];
    //     preOrder.pop_front();
    //
    //     if (isBetween(preOrder, min, data))
    //         left = new BST (preOrder, min, data);
    //     if (isBetween(preOrder, data, max))
    //         right = new BST (preOrder, data, max);
    // }

    BST (deque<int> levelOrder) {
        if (levelOrder.empty())
            return;

        data = levelOrder[0];
        levelOrder.pop_front();

        queue<pair<BST*, pair<int, int>>> nodesQueue;
        nodesQueue.push(range(this, 0, 1001));

        while (!nodesQueue.empty()) {
            int sz = nodesQueue.size();

            while (sz--) {
                BST *curr = nodesQueue.front().first;
                int min = nodesQueue.front().second.first;
                int max = nodesQueue.front().second.second;
                nodesQueue.pop();

                if (isBetween(levelOrder, min, curr->data)) {
                    int newData = levelOrder[0];
                    levelOrder.pop_front();
                    curr->left = new BST (newData);
                    nodesQueue.push(range(curr->left, min, data));
                }

                if (isBetween(levelOrder, curr->data, max)) {
                    int newData = levelOrder[0];
                    levelOrder.pop_front();
                    curr->right = new BST (newData);
                    nodesQueue.push(range(curr->right, data, max));
                }
            }
        }
    }

    pair<BST*, pair<int, int>> range(BST* node, int min, int max) {
        pair<int , int> range = make_pair(min, max);
        return make_pair(node, range);
    }

    bool isBetween(deque<int> &preOrder, int min, int max) {
        if (preOrder.empty())
            return false;
        return min < preOrder[0] && preOrder[0] < max;
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

    void successorQueries(deque<int>& q, vector<int> &answer, vector<int> &traversal) {
        if (q.empty())
            return;
        if (left && q.front() < data) {
            left->successorQueries(q, answer, traversal);
            if (q.empty())
                return;
        }

        if (!traversal.empty() && traversal.back() == q.front()) {
            answer.push_back(data);
            q.pop_front();
            if (q.empty())
                return;
        }
        traversal.push_back(data);

        if (right && q.front() >= data)
            right->successorQueries(q, answer, traversal);
    }

    bool isDegenerate(const vector<int> &preorder) {
        int min = 0, max = 1000;
        for (int i = 1; i < static_cast<int>(preorder.size()); i++) {
            if (preorder[i] < min || preorder[i] > max)
                return false;
            if (preorder[i] > preorder[i - 1])
                min = preorder [i - 1] + 1;
            else if (preorder[i] < preorder[i -1])
                max = preorder[i - 1] - 1;
        }
        return true;
    }
};

int main() {
    deque<int> v {50, 20, 60, 15, 45, 70, 35, 73};
    BST tree (v);
    tree.print_inorder();
}