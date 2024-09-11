// Another design to the stack is to make it implement two different stack using the same array 
// Why would we need that? I have no idea, I hope future me did.
#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int top1 { };
	int top2 { };
	int* array { };
public:
	Stack(int size) :
			size(size), top1(-1), top2(size) {
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(int id, int x) {
		assert(!isFull());
		if (id == 1)
			array[++top1] = x;
		else
			array[--top2] = x;
	}

	int pop(int id) {
		assert(!isEmpty(id));
		if (id == 1)
			return array[top1--];
		return array[top2++];
	}

	int peek(int id) {
		assert(!isEmpty(id));
		if (id == 1)
			return array[top1];
		return array[top2];
	}

	int isFull() {
		return top1 + 1 >= top2;
	}

	int isEmpty(int id) {
		if (id == 1)
			return top1 == -1;
		return top2 == size;
	}

	void display() {
		for (int i = top1; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
		for (int i = top2; i < size; i++)
			cout << array[i] << " ";
		cout << "\n";
	}
};
