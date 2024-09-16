// I used too much help on this one I must re-do it again sometime alone
#include <iostream>
#include <cassert>
using namespace std;

struct StackElement {
    int n;      // That's the replacement of arguments in funcitons (function's input)
    int result { -1};   // That's like the result of the function   (function's output)

    StackElement(int n = 1, int result = -1) :
        n(n), result(result) {
    }
    bool is_computed() {
        return result >= 0;
    }
};



class Stack {
private:
    int size { };
    int top { };
    StackElement *array { };

public:
    Stack(int size) :
			size(size), top(-1) {
		array = new StackElement[size] { };
	}

	~Stack() {
		delete[] array;
	}

	void push(StackElement x) {
		assert(!isFull());
		array[++top] = x;
	}

	StackElement pop() {
		assert(!isEmpty());
		return array[top--];
	}

	StackElement peek() {
		assert(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}

};

    int factorial(int x) {
        if (x <= 1) {
            return 1;
        }
        int subResult = factorial(x - 1);
        return x * subResult;
    }

    int factorial_stack(int x) {
        if (x <= 1)
            return 1;

        Stack stck(x);
        stck.push(StackElement(x));
        StackElement cur(1);
        
        while (!stck.isEmpty()) {
            cur = stck.peek();

            if (!cur.is_computed()) {
                if (cur.n <= 1) {
                    cur.result = 1;
                    stck.pop();
                    stck.push(cur);
                    
                }else
                    stck.push(StackElement(cur.n - 1));
            }
            else {
                cur = stck.pop();
                if (!stck.isEmpty()) {
                    StackElement parent = stck.pop();
                    parent.result = parent.n * cur.result;
                    stck.push(parent);
                }
            }
        }
        return cur.result;
    }
int main() {
    int x = 5;
    cout << factorial(x);
}