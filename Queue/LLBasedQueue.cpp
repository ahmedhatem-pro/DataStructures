#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int data {};
    Node* next {};
    Node(int data)  :  data(data) {}
};

class Queue {
private:
    Node *head {};
    Node *tail {};
    int length = 0;
public:
    Queue() : head(nullptr), tail(nullptr), length(0) {}
    ~Queue() {
        while (head) {
            Node* current = head;
            head = head->next;
            delete current;
        }
        tail = nullptr;
        length = 0;
    }
    void display (){
        Node* tempHead = head;
        while (tempHead != nullptr){
            cout << tempHead -> data << " ";
            tempHead = tempHead -> next;
            }
        cout << "\n";
        }

    void enqueue (int value){
        Node* item = new Node (value);
        if(!head)
            head = tail = item;
        else {
            tail -> next = item;
            tail = item;
        }
        length ++;
    }

    void dequeue (){
        if(!head)
        return;
        else {
            Node* current = head->next;
            delete head;
            head = current;
        }
        length --;
    }

    bool is_empty() {
        return length == 0;
    }
};
