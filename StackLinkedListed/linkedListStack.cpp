#include <iostream>
#include <cmath>
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

char convertIntToChar(int asciiValue) {
    return static_cast<char>(asciiValue);
}

double applyOp(double a, double b, char op) {

    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

double evaluate_infix(string infix) {   //I need to figure out how can I make the stack return double instead of int
    double result { };
    Stack values;
    Stack op;

    for (size_t i = 0; i < infix.length(); i++) {
        if (isspace(infix[i]))
            continue;
        if (isdigit(infix[i])) {
            double value = 0;
            while (i < infix.length() && isdigit(infix[i])) {
                value = (value * 10) + (infix[i] - '0');
                i++;
            }
            values.push(value);
            i--;
        }else {
            while (!op.isEmpty() && precedence(op.peek()) >= precedence(infix[i])) {
                if (precedence(infix[op.peek() == 3])){
                double val1 = values.pop();
                double val2 = values.pop();
                char ops = op.pop();
                values.push(applyOp(val1, val2, ops));
                values.display();
                } else {
                double val2 = values.pop();
                double val1 = values.pop();
                char ops = op.pop();
                values.push(applyOp(val1, val2, ops));
                }
            }
            op.push(infix[i]);
            }
        }
            while (!op.isEmpty()) {
                if (precedence(infix[op.peek() == 3])){
                double val1 = values.pop();
                double val2 = values.pop();
                char ops = op.pop();
                values.push(applyOp(val1, val2, ops));
                values.display();
                } else {
                double val2 = values.pop();
                double val1 = values.pop();
                char ops = op.pop();
                values.push(applyOp(val1, val2, ops));
                }
            }
        result = values.pop();
        return result;
}

double evalaute_postfix(string postfix) {   //I need to figure out how can I make the stack return double instead of int
	Stack numbers;

	for (int i = 0; i < (int) postfix.size(); ++i) {
		if (isdigit(postfix[i]))
			numbers.push(postfix[i] - '0');
		else {
			double a = numbers.pop();
			double b = numbers.pop();
			// Careful: b, a NOT a, b: consider 8/2 ==> 82/  a = 2, b = 8
			numbers.push(applyOp(b, a, postfix[i]));
		}
	}
	return numbers.pop();
}
int main() {
    string str = "23452*-*93/6+*+";
    cout << evalaute_postfix(str);
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