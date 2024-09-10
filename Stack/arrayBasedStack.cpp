#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class Stack {
private:
    int size { };
    int top { };
    int *array { };

public:
    Stack(int size) : size(size), top(-1) {
        array = new int[size];
    }

	~Stack() {
		delete[] array;
	}
	void push(int x) {
		assert(!isFull());
		array[++top] = x;
	}

	int pop() {
		assert(!isEmpty());
		return array[top--];
	}

	int peek() {
		assert(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}

	void display() {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}

};
	string reverse_subwords(string line) {
		string result;

		line += ' ';
		Stack stk(line.size());
		for (int i = 0; i < (int)line.size(); ++i) {
			if (line[i] == ' ') {
				while (!stk.isEmpty())
					result += stk.pop();
				result += ' ';
			} else
				stk.push(line[i]);
		}
		return result;
    }

	int reverse_num(int num) {
		if (num == 0) {
			return 0;
		}
		
		string string_num = to_string(num);
		Stack s(string_num.size());
		while (num) {
			s.push(num % 10);
			num /= 10;
		}
		int tens = 1;
		while (!s.isEmpty()) {
			num = s.pop() * tens + num;
			tens *= 10;
		}
		return num;
	}

int main() {
	int x = 9876;
	cout << reverse_num(x);
	return 0;
}