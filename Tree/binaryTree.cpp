#include <atomic>
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <stack>
using namespace std;

class BinaryTree {
private:
	int data { };
	BinaryTree* left { };
	BinaryTree* right { };

public:
	explicit BinaryTree(int data) :
			data(data) {
	}

	~BinaryTree() {
		clear();
	}

	void clear() {
		// Don't try to call clear for children and also delete. this deletes twice!
		if (left) {
			delete left; // recursively delete
			left = nullptr;	// good practice
		}
		if (right) {
			delete right;
			right = nullptr;
		}
	}

	void print_inorder() {
		if(left)
			left->print_inorder();
		cout << data << " ";
		if(right)
			right->print_inorder();
	}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		BinaryTree* current = this;

		for (int i = 0; i < static_cast<int>(values.size()); ++i) {
			if (direction[i] == 'L') {
				if (!current->left)
					current->left = new BinaryTree(values[i]);
				else
					assert(current->left->data == values[i]);
				current = current->left;
			} else {
				if (!current->right)
					current->right = new BinaryTree(values[i]);
				else
					assert(current->right->data == values[i]);
				current = current->right;
			}
		}
	}

	int treeMax() {
		int max = this->data;
		if (left) {
			if (left->treeMax() > max)
				max = left->treeMax();
		}
		if (right) {
			if (right->treeMax() > max)
				max = right->treeMax();
		}
		return max;
	}

	int treeHeight() {
		int maxHeight = 0;
		if (left)
			maxHeight = 1 + left->treeHeight();
		if (right)
			maxHeight = max(maxHeight, 1 + right->treeHeight());
		return maxHeight;
	}

	int countNodes() {
		int nodeCount = 1;
		if (left)
			nodeCount+= left->countNodes();
		if (right)
			nodeCount+=right->countNodes();
		return nodeCount;
	}

	int countLeaf() {
		int leafCount = 0;
		if (left) {
			leafCount+= left->countLeaf();
		}
		if (right) {
			leafCount+=right->countLeaf();
		}
		if (!right && !left)
			return 1;
		return leafCount;
	}

	bool doesExist(int item) {
		bool found = false;
		if (data == item) {
			found = true;
			return found;
		}
		if (left && found == false)
			found = left->doesExist(item);
		if (right && found == false)
			found = right->doesExist(item);
		return found;
	}

	bool isPerfect(int h = - 1) {
		if (h == -1)
			h = treeHeight();

		if (!left && !right)
			return  h == 0;

		if (!left && right || left && !right)
			return false;

		return left->isPerfect(h - 1) && right->isPerfect(h - 1);
	}

	bool isPerfectFormula() {
		int totalHeight = treeHeight();
		int totalNodes = countNodes();
		return pow(2, totalHeight + 1) - 1 == totalNodes;
	}

	void printInOrderIterative() {
		stack<pair<BinaryTree*, bool>> nodes;
		nodes.push(make_pair(this, false));

		while (!nodes.empty()) {
			BinaryTree* current = nodes.top().first;
			bool isComputed = nodes.top().second;
			nodes.pop();
			if (isComputed)
				cout << current->data << " ";
			else {
				if (current->right)
					nodes.push(make_pair(current->right, false));
				nodes.push(make_pair(current, true));
				if (current->left)
					nodes.push(make_pair(current->left, false));
			}
		}
		cout << "\n";
	}


};

int main() {
	BinaryTree tree(2);
	tree.add( { 3, 14 }, { 'L', 'L' });
	tree.add( { 3, 15 }, { 'L', 'R' });
	tree.add( { 13, 19 }, { 'R','L'  });
	tree.add( { 13 , 20}, { 'R', 'R' });
	tree.printInOrderIterative();
	return 0;
}