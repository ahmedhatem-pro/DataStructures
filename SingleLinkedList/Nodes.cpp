#include <iostream>
using namespace std;

struct Node {
    int data {};
    Node* next {};
    Node(int data)  :  data(data) {}
};

void print1(Node* head){
    while (head != nullptr) {
        cout << head -> data << " ";
        head = head -> next;
    }
    cout << "\n";
}

void print2(Node* head){
    if (head == nullptr)
    {
        cout << "\n";
        return;
    }
        cout << head -> data << " ";
        print2(head -> next);
    
}

void print3_reversed(Node* head){
    if (head == nullptr)
    {
        return;
    }
        print3_reversed(head -> next);
        cout << head -> data << " ";
    
}

void print4(Node* head){
    for (;head ; head = head->next){
        cout << head ->data << " ";
    }
}

Node* find(Node* head, int value){
    Node* tempNode = head;
    while (tempNode != nullptr) {
        if (tempNode -> data == value){
        cout << "Item found!! \n";
        return tempNode;
    }
        else {
            tempNode = tempNode -> next;
        }
    }
    cout << "Item not found.\n";
    return nullptr;
}
int main (){
    Node* node1 = new Node(6);
	Node* node2 = new Node(10);
	Node* node3 = new Node(8);
	Node* node4 = new Node(15);

    node1 ->next = node2;
    node2 ->next = node3;
    node3 ->next = node4;
    node4 ->next = nullptr;
    print4 (node1);
}