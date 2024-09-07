#include <iostream>
#include <cassert>
using namespace std;

struct ArrayNode {
    int data { };
    int index { };
    ArrayNode* next { };
    ArrayNode* prev { };

    ArrayNode(int data, int index) : data(data), index(index){ }
};

class ArrayLinkedList {
private:
    ArrayNode *head { };
    ArrayNode *tail { };
    int length = 0;
    int array_length { };

    void link(ArrayNode* first, ArrayNode* second) {
        if (first) {
            first->next = second;
        }
        if (second) {
            second->prev = first;
        }
    }

    ArrayNode* embed_after(ArrayNode* node_before, int data, int index) {
        ArrayNode* middle = new ArrayNode(data, index);
        ++length;

        ArrayNode* node_after = node_before->next;
        link(node_before,middle);
        
        if (!node_after) {
            tail = middle;
        }
        else
            link(middle, node_after);
        
        return middle;
    }

    ArrayNode* get_index(int index, bool is_create_if_missing) {
        ArrayNode* prev_index = head;
        while (prev_index->next && prev_index->next->index < index) {
            prev_index = prev_index->next;
        }
        bool found = prev_index->next && prev_index->next->index == index;

        if (found) {
            return prev_index->next;
        }
        if (!is_create_if_missing) {
            return nullptr;
        }
        return embed_after(prev_index, 0, index);
    }

public:
    ArrayLinkedList(int array_length) : array_length(array_length) {
        tail = head = new ArrayNode(0, -1);
        ++length;
    }

    void print_array() {
        ArrayNode* cur = head->next;

        for (int c = 0; c < array_length; c++) {
            if(cur && cur->index == c) {
                cout << cur->data << " ";
            } else
                cout << "0 ";
        }
        cout << "\n";
    }

    void print_array_nonzero() {
        for (ArrayNode *cur = head->next; cur; cur = cur->next)
            cout << cur->data << " ";
        cout<<"\n";
    }

    void set_value (int data, int index) {
        get_index(index, true)->data = data;
    }

    int get_value(int index) {
        ArrayNode *node = get_index(index, false);
        if(!node)
            return 0;
        return node->data;
    }

    void add(ArrayLinkedList &other) {
        assert(array_length == other.array_length);
        
        for (ArrayNode* other_cur = other.head->next; other_cur; other_cur->next) {
            ArrayNode* this_index = get_index(other_cur->index, true);
            this_index->data += other_cur->data;
        }
        // Make this function more efficient later
    }

};