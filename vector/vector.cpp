#include <iostream>
#include <cassert>
using namespace std;
class Vector {
private :
    int *arr = nullptr;
    int size = 0;   // User size
    int capacity;   // Actual size
public:
    Vector(int size):
    size(size){
        if (size < 0)
			size = 1;
        capacity = size * 2;
		arr = new int[capacity] { };
    }

    ~Vector(){
        delete[] arr;
        arr = nullptr;
    }
    
    int getSize(){
        return size;
    }

    int get (int idx){
		assert(0 <= idx && idx < size);
        return arr[idx];
    }

    void set (int idx, int val){
		assert(0 <= idx && idx < size);
        arr[idx] = val;
    }

	void print() {
		for (int i = 0; i < size; ++i)
			cout << arr[i] << " ";
		cout << "\n";
	}

	int find(int value) {
		for (int i = 0; i < size; ++i)
			if (arr[i] == value)
				return i;
		return -1;	// -1 for NOT found
	}


    void expandCapacity(){
        capacity *= 2;
        cout << "Expand capcity to " << capacity << "\n";
        int *arr2 = new int[capacity]{ };
        for (int i = 0; i < size; ++i)
            arr2[i] = arr[i];

        swap(arr, arr2);
        delete[] arr2;
    }

    void pushBack(int value){
        if (size == capacity)
        expandCapacity();
        arr[size++]=value;
    }

    void insert(int idx, int value){
        assert(0<=idx && idx < size);

        if (size == capacity)
            expandCapacity();

        for (int p = size-1; p>= idx; --p)
            arr[p+1]= arr[p];

        arr[idx] = value;
        size++;
    }

    // void rotateRight() {
    //     int *arr2 = new int[size];
	// 	int last = arr [size-1];
	// 	for (int i = 1 ; i <size ; ++i)
	// 		arr2[i] = arr[i-1];
	// 	arr2[0] = last;
	// 	swap(arr, arr2);
	// 	delete[] arr2;
	// 	}
    void rotateRight() {
        int *arr2 = new int[size];
		int last = arr [size-1];
		for (int i = size-2 ; i >= size ; --i)
			arr[i+1] = arr[i];
		arr[0] = last;
		}

	// void rotateLeft() {
    //     int *arr2 = new int[size];
	// 	int first = arr [0];
	// 	for (int i = 0 ; i < size-1 ; ++i)
	// 		arr2[i] = arr[i + 1];
	// 	arr2[size - 1] = first;
	// 	swap(arr, arr2);
	// 	delete[] arr2;
    // }
	void rotateLeft() {
		int first = arr [0];
		for (int i = 1 ; i < size ; ++i)
			arr[i-1] = arr[i];
		arr[size - 1] = first;
    }

	// void rotateRight(int times) {    //Used recursion as a practice
	// 	if (times == 0){
	// 		return;
	// 	}
    //     int *arr2 = new int[size];
	// 	int last = arr [size-1];
	// 	for (int i = 1 ; i <size ; ++i)
	// 		arr2[i] = arr[i-1];
	// 	arr2[0] = last;
	// 	swap(arr, arr2);
	// 	delete[] arr2;
	// 	rotateRight(--times);
	// }
	void rotateRight(int times) {
        times %= size;
		if (times == 0){
			return;
		}
        int *arr2 = new int[size];
		int last = arr [size-1];
		for (int i = 1 ; i <size ; ++i)
			arr2[i] = arr[i-1];
		arr2[0] = last;
		swap(arr, arr2);
		delete[] arr2;
		rotateRight(--times);
	}

	void rotateLeft(int times) {    //Used while-loop for practice
		while (times--){
        rotateLeft();
		}
	}

    // int pop(int idx){
    //     assert(0 <= idx && idx < size);
	// 	int deleteVal = arr[idx];
    //     int *arr2 = new int[size-1];
    //     for (int i = 0; i < size; ++i) {
    //         if (i < idx) {
    //             arr2[i] = arr[i];
    //         }
    //         else if (i > idx) {
    //             arr2[i - 1] = arr[i];
    //         }
    //     }
    //     size--;
	// 	swap(arr, arr2);
	// 	delete[] arr2;
	// 	return deleteVal;
	// }

    int pop(int idx){
        assert(0 <= idx && idx < size);
		int deleteVal = arr[idx];

        for (int i = idx + 1 ; i < size; ++i) {
            arr[i - 1] = arr[i];
        }
        size--;
		return deleteVal;
	}

	// int findTransposition(int value) {
	// 	int found = find(value);
    //     int *arr2 = new int[size];

    //     if (found == -1){
    //         return -1;
    //     }
    //     else {
    //         for (int i = size-1 ; i >= 0 ;--i)
    //             if (i == found && i > 0){
    //                 arr2[i] = arr[i-1];
    //                 arr2[i-1] = arr[i];
    //                 --i;
    //             }
    //             else
    //                 arr2[i] = arr[i];
    //     }
    //     swap(arr, arr2);
	// 	delete[] arr2;
	// 	return -1;	// -1 for NOT found
	// }
	int findTransposition(int value) {
        for(int i = 0; i < size; ++i)
            if(arr[i] == value ){
                if (i == 0)
                    return 0;
                swap(arr[i], arr[i - 1]);
                return i - 1;  // NOT i
            }
		return -1;	// -1 for NOT found
	}
};

int main () {
    Vector v(10);
	for (int i = 0; i < 10; ++i){
        v.set(i, i);
    }
    v.print();
	v.findTransposition(2);
    v.print();

}