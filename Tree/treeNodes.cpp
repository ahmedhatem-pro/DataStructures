#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int data { };
    Node* right { };
    Node* left { };
    Node (int data) : data (data) {};
};
    void print_inorder(Node* current) { //LVR way to print
        if (!current)
            return;
        print_inorder(current->left);
        cout << current->data << " ";
        print_inorder(current->right);
    }

    void print_postorder(Node* current) {// LRV
        if (!current) {
            return;
        }
        print_postorder(current->left);
        print_postorder(current->right);
        cout << current->data << " ";
    }

    void print_preorder(Node* current) {//VLR
        if (!current) {
            return;
        }
        cout << current->data << " ";
        print_preorder(current->left);
        print_preorder(current->right);
    }

    void clear(Node* current) {
        if(!current)
            return;
        clear(current->left);
        clear(current->right);
        delete current;
        cout << "Memory allocated" << endl;
    }


int main () {
    Node* plus = new Node('+');
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    plus->left = node2;
    plus->right = node3;
    Node* multiply = new Node('*');
    Node* node4 = new Node(5);
    multiply->left = plus;
    multiply->right = node4;
    clear(multiply);
}
