#include <atomic>
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
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

	explicit BinaryTree(string postfix) {
		stack <BinaryTree*> tree;

		for (int i = 0; i < static_cast<int>(postfix.size()); i++) {
			BinaryTree* current = new BinaryTree (postfix[i]);

			if (!isdigit(postfix[i])) {
				current->right = tree.top();
				tree.pop();
				current->left = tree.top();
				tree.pop();
			}
			tree.push(current);
		}
		BinaryTree* root = tree.top();
		this->data = root->data;
		this->left = root->left;
		this->right = root->right;
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

	bool isLeaf() {
		if (left || right)
			return false;
		return true;
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

	void traverse_left_boundary() {
		cout << data << " ";
		if (left)
			left->traverse_left_boundary();
		else if (right)
			right->traverse_left_boundary();
	}

	pair<int , int> treeDiameter() { // return diameter and height
		pair <int, int> result = make_pair(0, 0);

		if (!left && !right)
			return result;
		pair<int, int> leftDiameter = make_pair(0, 0);
		pair<int, int> rightDiameter = make_pair(0, 0);

		if (left) {
			leftDiameter = left->treeDiameter();
			result.first += 1 + leftDiameter.second;
		}
		if (right) {
			rightDiameter = right->treeDiameter();
			result.first += 1 + rightDiameter.second;
		}

		result.first = max(result.first, max(leftDiameter.first, rightDiameter.first));

		result.second = 1 + max(leftDiameter.second, rightDiameter.second);

		return result;
	}

	void printInOrderExpression() {
		if (left) {
			if (!left->isLeaf())
				cout << "(";
			left->printInOrderExpression();
			if (!left->isLeaf())
				cout<< ")";
		}

		cout << data ;

		if (right) {
			if (!right->isLeaf())
				cout << "(";
			right->printInOrderExpression();
			if (!right->isLeaf())
				cout<< ")";
		}
	}

	void levelOrderTraversal() {
		queue<BinaryTree*> nodes;
		nodes.push(this);

		while (!nodes.empty()) {
			BinaryTree* current = nodes.front();
			nodes.pop();
			cout << current->data << " ";

			if (current->left)
				nodes.push(current->left);
			if (current->right)
				nodes.push(current->right);
		}
		cout << "\n";
	}

	void levelOrderTraversal2() {
		queue<BinaryTree*> nodes;
		nodes.push(this);

		int level = 0;
		while (!nodes.empty()) {
			int sz = nodes.size();

			cout << "level " << level << ": ";
			while (sz--){
				BinaryTree* current = nodes.front();
				nodes.pop();
				cout << current->data << " ";

				if (current->left)
					nodes.push(current->left);
				if (current->right)
					nodes.push(current->right);
			}
		level++;
		cout << "\n";
		}
	}

	void printNodesLevel(int level) {
		if (level == 0)
			cout << data << " ";
		else if (level) {
			left->printNodesLevel(level - 1);
			right->printNodesLevel(level - 1);
		}
	}
	void recursiveLevelOrderTraversal() {	// works only on perfect trees
		int height = treeHeight();
		for (int level = 0; level <= height; level++
			)
			printNodesLevel(level);
	}

	void levelOrderTraversalSpiral() {
		deque<BinaryTree*> nodes;
		nodes.push_back(this);

		int level = 0;
		bool forwardLevel = true;

		while (!nodes.empty()) {
			int sz = nodes.size();

			cout << "Level " << level << ": ";
			while (sz--) {
				BinaryTree* current;

				if (forwardLevel) {
					current = nodes.front();
					nodes.pop_front();
					if (current->left)
						nodes.push_back(current->left);
					if (current->right)
						nodes.push_back(current->right);
				} else {
					current = nodes.back();
					nodes.pop_back();

					if (current->right)
						nodes.push_front(current->right);
					if (current->left)
						nodes.push_front(current->left);
				}
				cout << current->data << " ";
			}
		forwardLevel = !forwardLevel;
		level++;
		cout << "\n";
		}
	}

	bool isComplete() {
		queue<BinaryTree*> nodes;
		nodes.push(this);
		bool noMoreAllowed = false;

		while (!nodes.empty()) {
			int sz = nodes.size();

			while (sz--) {
				BinaryTree* current = nodes.front();
				nodes.pop();

				if ( current->left) {
					if (noMoreAllowed)
						return false ;
					nodes.push(current->left);
				} else
					noMoreAllowed = true;

					if (current->right) {
						if (noMoreAllowed)
							return false;
						nodes.push(current->right);
					} else
						noMoreAllowed = true;
			}
		}
		return true;
	}
};

int main() {
	BinaryTree tree(1);
	tree.add( { 2, 4 }, { 'L', 'L' });
	tree.add( { 2, 5 }, { 'L', 'R' });
	tree.add( { 3, 6 }, { 'R', 'L' });
	tree.add( { 3, 7 }, { 'R', 'R' });
	cout << tree.isComplete();
}