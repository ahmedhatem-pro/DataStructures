#include <iostream>
#include <cassert>

using namespace std;

class Stack {
private:
    struct Node {   //Note we can make the struct inside the class this allows for encapsulation as node struct is now more private
        int data { };
        Node* next { };

        Node(int data) :
            data(data) {
            }
    };

    Node* head{ };

public:
    ~Stack() {
		while (!isEmpty())
			pop();
	}

    void push(int value) {
        Node* item = new Node(value);

        item->next = head;
		head = item;
    }

    int pop() {
        assert(!isEmpty());

        int element = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return element;
    }

    int peek() {
		assert(!isEmpty());
		int element = head->data;
		return element;
	}

    int isEmpty() {
		return !head;
	}

    void display() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

};

string infix_to_postfix(string infix) {
    Stack operators;
    string postfix;

    for (char x : infix) {
        if (x == '*' || x == '/')
            operators.push(x);
        else if (x == '+' || x == '-') {
                if (operators.isEmpty())
                    operators.push(x);
                else {
                    while (!operators.isEmpty())
                        postfix += operators.pop();
                    operators.push(x);
                }
        }
        else
            postfix += x;
    }

    while (!operators.isEmpty()) {
            postfix += operators.pop();
    }

    return postfix;
}

int main() {
    string str = "1+3*5-8/2";
    cout << infix_to_postfix(str);
}
// Professor's code
// int precedence(char op) {
//     if (op == '+' || op == '-')
//         return 1;
//     if (op == '*' || op == '/')
//         return 2;
//     return 0;
// }

// string infixToPostfix(string infix) {
// 	Stack operators;
// 	string postfix;

// 	infix += '-';		// Whatever lowest priority: force stack got empty
// 	operators.push('#');// Remove IsEmpty

// 	for (int i = 0; i < (int) infix.size(); ++i) {
// 		if (isdigit(infix[i]))
// 			postfix += infix[i];
// 		else {
// 			while (precedence(operators.peek()) >= precedence(infix[i]))
// 				postfix += operators.pop();
// 			operators.push(infix[i]);
// 		}
// 	}

// 	return postfix;
// }