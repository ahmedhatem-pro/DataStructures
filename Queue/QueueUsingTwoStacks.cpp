#include <iostream>
#include <cassert>
using namespace std;
/*
Note the trick here was 1 Stack is normal and the other is reversed so
you can have one of the two main operations of the Queue (enqueue & dequeue)
have time complexity O(1) while the other is O(n) but you can't have both O(1)
*/
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

class Queue {
private:
    int size;
    int added_elements;
    Stack s1;
    Stack s2;

    void move(Stack& from, Stack& to) {
        while (!from.isEmpty()) {
            to.push(from.pop());
        }
        
    }
public:
    Queue(int size) : size(size), s1(size), s2(size){}
    void enqueue (int value){
        assert(!isFull());
        move(s1, s2);
        s1.push(value);
        move(s2, s1);
        added_elements++;
    }

    int dequeue (){
        assert(!isEmpty());
        int value = s1.pop();
        --added_elements;
        return value;
    }

    bool isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }
};