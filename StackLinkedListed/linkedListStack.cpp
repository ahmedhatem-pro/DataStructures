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
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;

    return 0;
}

string infix_to_postfix(string infix) { // TODO: Revisit this function to handle more complicated cases and improve functionality. Take this case for example (-25+5log(11! *5^3^12))
    Stack operators;
    string postfix;

    for (char x : infix) {
        if (x == '(') {
            operators.push(x);
        } else if (x == ')') {
            while (!operators.isEmpty() && operators.peek() != '(')
                postfix += operators.pop();
            operators.pop();    // pop '('
            } else if (precedence(x) == 3)
                operators.push(x);
                else if (precedence(x) == 2) {
                    if (operators.isEmpty() && operators.peek() != '^')
                        operators.push(x);
                    else {
                        while (!operators.isEmpty() && operators.peek() != '(' && precedence(operators.peek()) == 3)
                            postfix += operators.pop();
                        operators.push(x);
                    }
                } else if (precedence(x) == 1) {
                                if (operators.isEmpty())
                                    operators.push(x);
                                else {
                                    while (!operators.isEmpty() && operators.peek() != '(')
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
    string str = "1+2^3^4*5-6";
    // string str = "5+4^3^2-9";   //5432^^+9-
    cout << infix_to_postfix(str);
}
// *Professor's code*
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

// 	infix += '-';			// Whatever lowest priority: force stack got empty
// 	operators.push('#');	// Remove IsEmpty

// 	for (int i = 0; i < (int) infix.size(); ++i) {
// 		if (isdigit(infix[i]))
// 			postfix += infix[i];
// 		else if (infix[i] == '(')
// 			operators.push(infix[i]);
// 		else if (infix[i] == ')') {
// 			while (operators.peek() != '(')
// 				postfix += operators.pop();
// 			operators.pop();	// pop (
// 		} else {
// 			while (precedence(operators.peek()) >= precedence(infix[i]))
// 				postfix += operators.pop();
// 			operators.push(infix[i]);
// 		}
// 	}

// 	return postfix;
// }