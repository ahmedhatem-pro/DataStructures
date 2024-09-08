#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
    int size { };
    int added_elements { };
    int *array { };

public:
    Stack(int size) : size(size) {
        array = new int[size];
    }

	~Stack() {
		delete[] array;
    }

	int isFull() {
		return added_elements == size ;
	}

    int isEmpty() {
        return added_elements == 0;
    }

    bool push(int x) {
        if (isFull)
            return false;
        for (int i = added_elements - 1;i >= 0; i--)
            array[i + 1] = array [i];
        array [0] = x;
        added_elements++;
        return true;
    }

    bool pop(int &result) {
        if (isEmpty)
            return false;
        result = array[0];
        for (int i = 0; i < added_elements - 1; i++)
            array [i] = array [i+1];
        added_elements --;
        return true;
    }

    bool peek(int &result) {
        if (isEmpty)
            return false;
        result = array[0];
        return true;
    }
};

	// void display() {
	// 	for (int i = top; i >= 0; i--)
	// 		cout << array[i] << " ";
	// 	cout << "\n";
	// }