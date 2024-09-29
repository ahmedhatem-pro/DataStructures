#include <iostream>
#include <cassert>
#include <vector>
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
		if(left) {
			if (left->treeMax() > max)
				max = left->treeMax();
		}
		if(right) {
			if (right->treeMax() > max)
				max = right->treeMax();
		}
		return max;
	}

	int treeHeight() {
		int maxHeight = 0;
		if(left)
			maxHeight = 1 + left->treeHeight();
		if (right)
			maxHeight = max(maxHeight, 1 + right->treeHeight());
		return maxHeight;
	}

	int countNodes() {
		int nodeCount = 1;
		if (left) {
			nodeCount+= left->countNodes();
		}
		if (right) {
			nodeCount+=right->countNodes();
		}
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
};

int main() {
	BinaryTree tree(2);
	tree.add( { 3 }, { 'L' });
	tree.add( { 13,7  }, { 'R' ,'L' });
	tree.add( { 13, 8 }, { 'R' ,'R' });
	cout << tree.countLeaf();
	return 0;
}