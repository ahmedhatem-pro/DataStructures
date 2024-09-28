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
};

int main() {
	BinaryTree tree(1);
	tree.add( { 36, 4, 7 }, {'L', 'L', 'L' });
	tree.add( { 36, 4, 7,100 }, {'L', 'L', 'L', 'R'});
	tree.add( { 36, 4, 16 }, {'L', 'L', 'R' });
	tree.add( { 36, 5, 9 }, {'L', 'R', 'R' });
	tree.add( { 3, 6, 10 }, {'R', 'R', 'L' });
	cout << tree.treeMax();
	return 0;
}