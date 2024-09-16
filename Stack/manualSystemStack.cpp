#include <iostream>
#include <cassert>
using namespace std;

struct StackElement {
    int n { };
    int result {-1};

    StackElement (int n = 1, int result = -1) : 
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
    Stack (int size):
        size(size), top(-1) {
        array = new StackElement[size] { };
        }
    ~Stack () {
        delete[] array;
    }

    int is_full() {
        return top == size - 1;
    }

    int is_empty() {
        return top == -1;
    }
    void push(StackElement n) {
        assert(!is_full());
        array[++top] = n;
    }

    StackElement pop() {
        assert(!is_empty());
        return array[top--];
    }

    StackElement peek() {
        assert(!is_empty());
        return array[top];
    }
};

int factorial(int x) {
    if(x <= 1)
        return 1;

    return x * factorial(x - 1);
}

int stackFactorial(int x) {
    if (x <= 1)
        return 1;
    
    Stack st(x);
    st.push(StackElement(x));
    StackElement cur(1);

    while (!st.is_empty()) {
        cur = st.peek();

        if (!cur.is_computed()){
            if (cur.n <= 1) {
                cur.result = 1;
                st.pop();
                st.push(cur);
            } else
                st.push(StackElement(cur.n - 1));
        } else {
            cur = st.pop();
            if (!st.is_empty()){
                StackElement parent = st.pop();
                parent.result = parent.n * cur.result;
                st.push(parent);
            }
        }
    }
    return cur.result;
}

int main() {
    cout << stackFactorial(5);
}