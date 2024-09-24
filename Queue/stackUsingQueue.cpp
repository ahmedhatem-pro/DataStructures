#include <iostream>
#include <cassert>
using namespace std;

class Queue {
	int size { };
	int front { 0 };
	int rear { 0 };
	int added_elements { };
	int *array { };

public:
	Queue(int size) :
			size(size) {
		array = new int[size];
	}

	~Queue() {
		delete[] array;
	}

	int next(int pos) {
		++pos;
		if (pos == size)
			pos = 0;
		return pos;
	}

	int prev(int pos) {
		--pos;
		if (pos == 0)
			pos = size - 1;
		return pos;
	}

	void enqueue(int value) {
		assert(!isFull());
		array[rear] = value;
		rear = next(rear);
		added_elements++;
	}

	int dequeue() {
		assert(!isEmpty());
		int value = array[front];
		front = next(front);
		--added_elements;
		return value;
	}

    int front_value(){
        return front;
    }
	void display() {
		cout << "Front " << front << " - rear " << rear << "\t";
		if (isFull())
			cout << "full";
		else if (isEmpty()) {
			cout << "empty\n\n";
			return;
		}
		cout << "\n";

		for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
			cout << array[cur] << " ";
		cout << "\n\n";
	}

	int isEmpty() {
		return added_elements == 0;
	}

	bool isFull() {
		return added_elements == size;
	}
};

class Stack
{
private:
    Queue q;
    int added_elements { };

    void insert_at_front(int value) {
        int sz = added_elements;
        q.enqueue(value);
        while (sz--)
            q.enqueue(q.dequeue());
        ++added_elements;
    }
public:
    void push(int value){
        insert_at_front(value);
    }

    int pop() {
        --added_elements;
        return q.dequeue();
    }

    int peek() {
        return q.front_value();
    }
};