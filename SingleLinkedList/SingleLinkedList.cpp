#include <iostream>
#include <cassert>
#include <climits>
#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;
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

    vector<Node*> debug_data;	// add/remove nodes you use

    // void DebugAddNode(Node* node) {
    //         debug_data.push_back(node);
    //     }

    void DebugRemoveNode(Node* node) {
            auto it = std::find(debug_data.begin(), debug_data.end(), node);
            if (it == debug_data.end())
                cout << "Node does not exist\n";
            else
                debug_data.erase(it);
        }
public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    ~LinkedList() {
        while (head) {
            Node* current = head;
            head = head->next;
            delete current;
        }
        tail = nullptr;
        length = 0;
    }
    void DeleteNode(Node* node) {
            DebugRemoveNode(node);
            --length;
            delete node;
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

    void OddPosEvenPoss() {  // O(n) time, O(1) space
    if (length <= 2) 
        return;
    Node *FirstEven = head->next;  
    Node *CurrentOdd = head;
    Node *CurrentEven = head->next;
    while (CurrentEven && CurrentEven->next) {
        CurrentOdd->next = CurrentEven->next;
        CurrentOdd = CurrentOdd->next;
        CurrentEven->next = CurrentOdd->next;
        CurrentEven = CurrentEven->next;
        }
    CurrentOdd->next = FirstEven;
    if (length % 2 == 0) {
        tail = CurrentEven;
        }
    else {
        tail = CurrentOdd;
        }
}

    void InsertAfter (Node *src, Node* target) {
        target->next = src->next;
        src->next = target;
        length++;
    }

    void InsertALternate(LinkedList &AnotherList) { // Incomplete function + Exception when destrcution 
        if (!AnotherList.length) {
            return;
        }
        if (!length) {
            head = AnotherList.head;
            tail = AnotherList.tail;
            length = AnotherList.length;
        }else{
            Node* current2 = AnotherList.head;
            for (Node* current1 = head; current1 && current2;) {
                Node* current2NextTemp = current2->next;
                InsertAfter(current1,current2);
                AnotherList.length--;
                current2 = current2NextTemp;
                if (current1 == tail){
                    tail = AnotherList.tail;
                    current1->next->next = current2;
                    length+=AnotherList.length;
                    break;
                }
                current1 = current1->next->next;
            }
        }
    }

    void AddNum (LinkedList &AnotherList) {
        if (length == 0 && length == 0){
            return;
        }
        if (head->data == 0 && AnotherList.head->data == 0){
            return;
        }
        int a = length, b = AnotherList.length;
        int DifferenceInLength = abs(a - b);
        if(length > AnotherList.length){
            while (DifferenceInLength-- ){
                AnotherList.InsertFront(0);
            }
        }else if(AnotherList.length > length) {
            while (DifferenceInLength-- ){
                InsertFront(0);
            }
        }
        Reverse();
        AnotherList.Reverse();
        int carry = 0;
        Node *Current = head;
        Node *AnotherCurrent = AnotherList.head;
        while (Current && AnotherCurrent){
            int SelfValue = Current->data;
            int AnotherValue = AnotherCurrent->data;
            int added = SelfValue + AnotherValue + carry;
            if(added >= 10){
                Current->data = (added % 10);
                carry = 1;
            }else{
                Current->data = (added);
                carry = 0;
            }
            Current = Current->next;
            AnotherCurrent = AnotherCurrent->next;
        }
        Reverse();
        if (carry == 1){
            InsertFront(1);
        }
        AnotherList.Reverse();
    }

    Node* MoveAndDelete(Node* node) {
        Node* temp = node->next;
        DeleteNode(node);
        return temp;
    }

    void RemoveReapetedValues() {
        if (length <= 1) {
            return;
        }
        InsertFront(-123546);
        tail = head;
        Node* previous = head;
        Node* current = head->next;
        while (current) {
            bool AnyRemoved = false;
            while (current && current->data == current->next->data) { // Segmentaion fault if the last element won't be deleted(No repetition)
                int BlockValue = current->data;
                AnyRemoved = true;
                while (current && current->data == BlockValue)
                    current = MoveAndDelete(current);
            }
            if (AnyRemoved) {
                if (!current)
                    tail = previous;
                previous->next = current;
                previous = current;
            }else{
                tail = current;
                previous = current;
                current = current->next;
            }
        }
        previous = head->next;
        DeleteHead();
        head = previous;
        if (!head)
            tail = head;
    }

    pair<Node*, pair<Node*, Node*>> ReverseSubChain(Node* CurHead, int k) {
        Node* CurTail = CurHead;
        Node* Prev = CurHead;
        CurHead = CurHead->next;
        for (int s = 0; s < k-1 && CurHead; s++) {
            Node* next = CurHead->next;
            CurHead->next = Prev;
            Prev = CurHead;
            CurHead = next;
        }
        return make_pair(Prev, make_pair(CurTail, CurHead));
    }
    void ReverseChains(int k) {  //Only God knows what happened here 
        if(length <= 1 || k == 1)
            return;
        Node* LastTail = nullptr;
        Node* nextChainHead = head;
        head = nullptr;
        while(nextChainHead) {
            pair<Node*, pair<Node*, Node*>> p = ReverseSubChain(nextChainHead, k);
            Node* chainHead = p.first;
            Node* chainTail = p.second.first;
            nextChainHead = p.second.second;
            tail = chainTail;

            if(!head)
                head = chainHead;
            else
                LastTail->next = chainHead;
            LastTail = chainTail;
        }
        tail->next = nullptr;
    }
};
