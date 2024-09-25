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
class PriorityQueue{
private:
    int size{ };
    int added_elements{ };
    Queue q1, q2, q3;
public:
    PriorityQueue(int size) : size(size),q1(size), q2(size), q3(size){}

    void enqueue(int task_id, int prio) {
        assert(!isFull());
        if (prio == 3)
            q3.enqueue(task_id);
        else if (prio == 2)
            q2.enqueue(task_id);
        else if (prio == 1)
            q1.enqueue(task_id);

        added_elements++;
    }

    void dequeue() {
        assert(!isEmpty());
        if (!q3.isEmpty())
            q3.dequeue();
        else if (!q3.isEmpty())
            q2.dequeue();
        else if (!q3.isEmpty())
            q1.dequeue();

        added_elements--;
    }

    void display() {
        for (int i = 0; i < 3; i++) {
            if (i == 0){
                cout << "Priority #3 tasks :";
                q3.display();}
            else if (i == 1){
                cout << "Priority #2 tasks :";
                q2.display();}
            else if (i == 2){
                cout << "Priority #1 tasks :";
                q1.display();}
        }
    }

    bool isFull(){
        return added_elements == size;
    }

    bool isEmpty(){
        return added_elements == 0;
    }
};