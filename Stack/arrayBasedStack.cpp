#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
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

	void display_reversed() {
		for (int i = 0; i <= top; i++)
			cout << array[i] << " ";
		cout << "\n";
	}

	void insert_at_bottom(int x) {
		if (isEmpty())
			push(x);
		else{
		int cur = pop();
		insert_at_bottom(x);
		push(cur);
		}
	}

	void reverse() { // [1, 2, 3, 4]  [4, 3, 2, 1]
		if(isEmpty())
			return;
		int cur = pop();

		reverse();

		insert_at_bottom(cur);
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

	bool is_valid(string str) { // valid parentheses
		Stack stck(str.size());
		for (char x : str) {
			if (x == ',' || x == ' ')
				continue;
			if (x == '(' || x == '{' || x == '[')
				stck.push(x);
			else if (stck.isEmpty())
				return false;
			else if (x == ')' && stck.peek() == '(')
				stck.pop();
			else if (x == ']' && stck.peek() == '[')
				stck.pop();
			else if (x == '}' && stck.peek() == '{')
				stck.pop();
			
			else
				return false;
		}
		return stck.isEmpty();
	}

	string remove_duplicates(string S) {
		Stack stck(S.size() - 1);
		string result;
		for (char x : S) {
			if (stck.isEmpty() || stck.peek() != x) {
				stck.push(x);
			}
			else if (stck.peek() == x)
				stck.pop();
		}
		
		Stack reversedStack(S.size());
		while (!stck.isEmpty()) {
			reversedStack.push(stck.pop());
		}
		while (!reversedStack.isEmpty()) {
			result += reversedStack.pop();
		}

		return result;
	}

	void asteroidCollision(int arr[], int len) {
		Stack result(len);

		for (int i = 0; i < len; ++i) {
		int asteroid = arr[i];
			bool is_exploded = false;
			while (!result.isEmpty() && asteroid < 0 && 0 <= result.peek()) {
				if (result.peek() < -asteroid) {
					result.pop();
					continue;	// See if more explode
				} else if (result.peek() == -asteroid)	// both exploded
					result.pop();
				is_exploded = true;
				break;
			}
			if (!is_exploded)
				result.push(asteroid);
		}
		result.display_reversed();
	}

	int parenthles_score(string str) {
		Stack stck(str.size());
		stck.push(0);

		for (char x : str) {
			if (x == '(')
				stck.push(0);
			else {
				int last = stck.pop();

				if (last == 0)
					last = 1;
				else 
					last *= 2;

				int parent_par = stck.pop() + last;
				stck.push(parent_par);
			}
		}
		return stck.peek();
	}

	void next_greater_element(int arr[], int len) {
		Stack indx(len);

		for (int i = 0; i < len; i++){
			while (!indx.isEmpty() && arr[indx.peek()] < arr[i])
				arr[indx.pop()] = arr[i];
			indx.push(i);
		}

		while (!indx.isEmpty())
			arr[indx.pop()] = -1;

		for (int i = 0; i < len; i++) {
			cout << arr[i] << " ";
		}
	}
int main() {
	const int length = 6;
	int arr[length] {30, 10, 5, 7, 15, 11};
	next_greater_element(arr, length);
	return 0;
}