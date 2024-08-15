#include <iostream>
#include <cassert>
#include <climits>
#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;
// Test1
struct Node {
    int data {};
    Node* next {};
    Node(int data)  :  data(data) {}
};
class ComplexLinkedList{
private:
    Node* head {};

public:

    void addElement (int value){
        Node* item = new Node (value);
        if(!head)
        head = item;
        else {
            item -> next = head;
            head = item;
        }
        
    }

    void print (){
        Node* tempHead = head; 
        while (tempHead != nullptr){
            cout << tempHead -> data << " ";
            tempHead = tempHead -> next;
            }
        cout << "\n";
    }
    Node* GetTail (){
        return head;
    }
};
class LinkedList {
private:
    Node *head {};
    Node *tail {};
    int length = 0;
public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    ~LinkedList() {             // O(n) time O(1) memory
            while (head) {
                Node* current = head->next;
                delete head;
                head = current;
            }
        }
    void print (){              // O(n) time O(1) memory
        Node* tempHead = head; // Don't change the head itself. You will lose it.
        while (tempHead != nullptr){
            cout << tempHead -> data << " ";
            tempHead = tempHead -> next;
            }
        cout << "\n";
        }

    Node* GetNth (int n){       // O(n) time O(1) memory
        int count = 0;
        for (Node* current = head; current ; current = current -> next)
            if (++count == n)
                return current;
            return nullptr;
        }

    Node* GetNthBack (int n){   // O(n) time O(1) memory
        int count = length;
        for (Node* current = head; current ; current = current -> next)
            if (--count == n)
                return current;
            return nullptr;
        }

    int Search (int n){         // O(n) time O(1) memory
        int indx = 0;
        for (Node* current = head; current ; current = current -> next){
            if (current -> data == n)
                return indx;
            indx ++;
            }
        return -1;
        }

    int ImprovedSearch (int n){         // O(n) time O(1) memory
        Node* Previous = head;
        int indx = 0;
        for (Node* current = head; current ; current = current -> next, indx ++){
            if (current -> data == n){
                if (!Previous){
                    return indx;
                    }
                swap(Previous -> data , current -> data);
                return indx - 1;
                }
            Previous = current;
                }
        return -1;
    }

    void InsertEnd (int value){         // O(1) time O(1) memory
        Node* item = new Node (value);
        if(!head)
            head = tail = item;
        else {
            tail -> next = item;
            tail = item;
        }
        length ++;
    }

    void InsertFront (int value){         // O(1) time O(1) memory
        Node* item = new Node (value);
        if(!head)
        head = tail = item;
        else {
            item -> next = head;
            head = item;
        }
        length ++;
    }

    void DeleteHead (){         // O(1) time O(1) memory
        if(!head)
        return;
        else {
            Node* current = head->next;
            delete head;
            head = current;
        }
        length --;
    }

    void DeleteTail (){         // O(1) time O(1) memory
        if(length <= 1){
        DeleteHead();
        return;
        }
        Node *previous = GetNth(length - 1);
        delete tail;
        tail = previous;
        tail->next = nullptr;
        length --;
    }

    void DeleteNthNode(int n){      // O(1) time O(1) memory
        if (n < 1 || n > length)
            cout << "There is no such node !!\n";
        else if (n == 1) 
                DeleteHead();
        else {
            Node *BeforeNthELement = GetNth(n - 1);
            Node *nth = BeforeNthELement->next;
            bool Istail = nth == tail;

            BeforeNthELement->next = nth->next;
            if (Istail){
                tail = BeforeNthELement;
            }
            delete nth;
            length --;
        }
    }

    void DeleteWithKey(int n){      // O(1) time O(1) memory
            Node *current = head;
            int DeletedKeyIndx = 1;
            while (current->next != nullptr){
                if (current->data == n){
                    DeleteNthNode(DeletedKeyIndx);
                    length --;
                    return;
                }
                current = current->next;
                DeletedKeyIndx++;
            }
    }

    void SwapEachPairValues(){      // O(n) time O(1) memory
        if (length < 2) {
            return;
            }
        Node *previous = head;
        Node *current = head->next;
        while (current != nullptr){
            swap(previous->data, current->data);
            previous = previous->next->next;
            if (previous != nullptr) {
            current = previous->next;
            }
            else {
                break;
            }
        }
    }

    void Reverse(){       // O(n) time O(1) memory
        if (length <= 1)
            return;

        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
        }

    void DeleteEvenPositions() {    // O(n) time O(1) memory
        if (length <= 1) {
            return;
        }
        Node* current = head->next;
        Node* previous = head;
        while (current != nullptr) {
            previous->next = current->next;
            delete current;
            previous = previous->next;
            if (previous == nullptr) 
                break;
            current = previous->next;
        }
    }

    void InsertSorted(int value){       // O(n) time O(1) memory
        Node* item = new Node (value);
        if(!head)
            head = tail = item;
        else if (head->data >= value)
            InsertFront(value);
        else if (tail->data <= value)
            InsertEnd(value);
        else {
            Node *previous = head;
            Node *following = head->next;
            for (; following ; previous = previous->next, following = following->next){
                if (previous->data <= value && following->data >= value){
                    previous->next = item;
                    item->next = following;
                    break;
                }
            }
        }
        length ++;
    }

    void HeadTailSwap() {           // O(n) time O(1) memory
        if (!head || !head->next) {
            return;
        }
        Node* tempNode = head;
        Node* current = head;
        while(current->next != tail)    //This is only to get the node before tail unfortunatlly that is the only O(n) step in the whole function
            current = current->next;
        tail->next = head->next;
        head->next = nullptr;
        current->next = head;
        head = tail;
        tail = tempNode;
    }

    void RotateLeft (){         // O(1) time O(1) memory
        if(length <= 1)
            return;
        Node *tempTail = tail;
        Node *tempHead = head;
        head = head->next;
        tail = tempHead;
        tail->next = nullptr;
        tempTail->next = tail;
    }

    void DeleteTheDuplicates() {        // O(n^2) time O(1) memory ~Note: Can be better once I learn about hashing
        for (Node *DuplicatedNumber = head; DuplicatedNumber != nullptr; DuplicatedNumber = DuplicatedNumber->next){
            Node *previous = DuplicatedNumber;
            Node *current = DuplicatedNumber->next;
            for (; current != nullptr; ){
                if (current->data == DuplicatedNumber->data){
                    previous->next = current->next;
                    delete current;
                    current = previous->next;
                } else {
                    previous = current;
                    current = current->next;
                }
            }
        }
    }

    void DeleteLastOccurrence (int key){        // O(n) time O(1) memory
        Node *DeletedNode = nullptr;
        Node *PreDeleted = nullptr;
        Node *PreCurrent = head;
        if (PreCurrent->data == key){
            DeletedNode = PreCurrent;

            }
        for (Node *current = head->next; current != nullptr; current = current->next, PreCurrent = PreCurrent->next){
            if (current->data == key){
                DeletedNode = current;
                PreDeleted = PreCurrent;
            }
        }
        if (DeletedNode != nullptr && PreDeleted != nullptr){
            PreDeleted->next = DeletedNode->next;
            delete DeletedNode;
        }
        else if (DeletedNode != nullptr && PreDeleted == nullptr)       //last occurence was the head of the list
                DeleteHead();
        else if (DeletedNode == nullptr && PreDeleted == nullptr)       //Key value doesn't exist in the list 
                cout << "That value doesn't exist in the list!!\n";
    }

    void MoveToBack(int key){       // Test case Failed (when the head has value like the key)
        Node *PreCurrent = head;
        Node *current = head->next;
        current = PreCurrent->next;
        Node *PostCurrent = current->next;
        Node *OriginalTail = tail;
        for (; current != OriginalTail; current = PostCurrent, PostCurrent = PostCurrent->next){
            if (current->data == key){
                tail->next = current;
                tail = current;
                current->next = nullptr;
                PreCurrent->next = PostCurrent;
            }
            else{PreCurrent = PreCurrent->next;}
        }
    }

    int Max(Node *current = nullptr) {      // O(n) time O(1) memory
        if (current == nullptr) {
            current = head;
            }
        if (current == nullptr) {
            cout <<"List is empty and has no Max value";
            return -1;
            }
        if (current->next == nullptr) {
            return current->data;
            }
        int maxInRest = Max(current->next);
        if (current->data > maxInRest) {
            return current->data;
            }
        else {
            return maxInRest;
            }
    }

    bool IsSame(const LinkedList& otherList) const {        // O(n) time O(1) memory
        Node* selfCurrent = head;
        Node* otherListCurrent = otherList.head;
        if (length != otherList.length)
            return false;
        else{
            while (selfCurrent != nullptr){
                if (selfCurrent -> data != otherListCurrent -> data){
                    return false;
                }
                selfCurrent = selfCurrent -> next;
                otherListCurrent = otherListCurrent -> next;
            }
        return true;
        }

    }

};

int main (){
    
    LinkedList list1;
    LinkedList list2;
    list2.Max();
    list2.HeadTailSwap();
    // list1.InsertEnd(6);
    // list1.InsertEnd(5);
    // list1.InsertEnd(5);
    // list1.InsertEnd(4);
    // list1.InsertEnd(4);
    // list1.InsertEnd(9);
    // list1.InsertEnd(4);
    // list1.print();
    // cout<<list1.Max();
    // list1.print();
}
