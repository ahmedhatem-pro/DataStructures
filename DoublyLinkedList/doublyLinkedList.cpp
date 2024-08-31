#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
	int data { };
	Node* next { };
	Node* prev { };

	Node(int data) : data(data) {}

	void set(Node* next, Node* prev) {
		this->next = next;
		this->prev = prev;
	}

	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class LinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;

	// let's maintain how many nodes

	vector<Node*> debug_data;	// add/remove nodes you use

	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

public:

	LinkedList() {
	}
	// Below 2 deletes prevent copy and assign to avoid this mistake
	LinkedList(const LinkedList&) = delete;
	LinkedList &operator=(const LinkedList &another) = delete;

	void debug_print_address() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}

	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}

		if (node->prev == nullptr)
			cout << "X\t";
		else
			cout << node->prev->data << "\t";

		cout << " <= [" <<node->data << "]\t => \t";

		if (node->next == nullptr)
			cout << "X\t";
		else
			cout << node->next->data << "\t";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int) debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}

	string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node* cur = head; cur; cur = cur->next) {
			oss << cur->data;
			if (cur->next)
				oss << " ";
		}
		return oss.str();
	}

	void debug_verify_data_integrity() {
		if (length == 0) {
			assert(head == nullptr);
			assert(tail == nullptr);
		} else {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!head->prev);
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++) {
			if (len == length-1)	// make sure we end at tail
				assert(cur == tail);
		}

		assert(length == len);
		assert(length == (int)debug_data.size());

		len = 0;
		for (Node* cur = tail; cur; cur = cur->prev, len++) {
			if (len == length-1)	// make sure we end at head
				assert(cur == head);
		}
		cout << "Data inegrity verified !\n";
	}
	////////////////////////////////////////////////////////////

	void print() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}

	void add_node(Node* node) {
		debug_add_node(node);
		++length;
	}

	void print_reversed()  {
		for (Node* cur = tail; cur; cur = cur->prev)
			cout << cur->data << " ";
		cout << "\n";
	}

	void link(Node* first, Node* second) {
		if(first)
			first->next = second;
		if(second)
			second->prev = first;
	}

	void insert_end(int value) {
		Node* item = new Node(value);
		add_node(item);

		if(!head) {
			head = tail = item;
		}
		else{
			link(tail, item);
			tail = item;
		}
		debug_verify_data_integrity();
	}

	void insert_front(int value) {
		Node* item = new Node(value);
		add_node(item);

		if(!head) {
			head = tail = item;
		}
		else{
			link(item, head);
			head = item;
		}
		debug_verify_data_integrity();
	}

	void embed_after(Node* node_before, int value) {
		Node* middile = new Node(value);
		++length;
		debug_add_node(middile);

		Node* node_after = node_before->next;
		link(node_before, middile);
		link(middile, node_after);
	}

	void insert_sorted(int value) {
		if (!length || value <= head->data)
			insert_front(value);
		else if (tail->data <= value)
			insert_end(value);
		else {
			for(Node *cur = head; cur; cur = cur->next) {
				if (value <= cur->data) {
					embed_after(cur->prev, value);
					break;
				}
			}
		}
	}

	void delete_front() {
		if (!head)
			return;
		Node* cur = head->next;
		delete_node(head);
		head = cur;

		// Integrity change
		if (head)
			head->prev = nullptr;
		else if (!length)
			tail = nullptr;

		debug_verify_data_integrity();
	}

	void delete_end() {
		if (!tail)
			return;
		Node* cur = tail->prev;
		delete_node(tail);
		tail = cur;

		// Integrity change
		if (tail)
			tail->next = nullptr;
		else if (!length)
			head = nullptr;

		debug_verify_data_integrity();
	}

	Node* delete_and_link(Node* cur) {
		Node* ret = cur->prev;
		link(cur->prev, cur->next);
		delete_node(cur);
		return ret;
	}

	void delete_node_with_key(int value) {
		if (!length)
			return;
		if (head->data == value)
			delete_front();
		else {
			for (Node* cur = head; cur; cur = cur->next) {
				if (cur->data == value) {
					cur = delete_and_link(cur);
					if (!cur->next)
						tail = cur;
					break;
				}
			}
		}
		debug_verify_data_integrity();
	}

	void delete_all_nodes_with_key(int value) {
		if (!length)
			return;

		insert_front(-value);

		for (Node* cur = head; cur;) {
			if (cur->data == value){
				cur = delete_and_link(cur);
			if(!cur->next)
				tail =cur;
			}else
				cur=cur->next;
		}

		delete_front();

		debug_verify_data_integrity();
	}

	void delete_even_positions() {
		if(length <= 1)
			return;

		for (Node* cur = head->next; cur;cur = cur->next->next) {
			cur = delete_and_link(cur);
			if (!cur->next) {
				tail = cur;
				break;
			}
		}
		debug_verify_data_integrity();
	}

	void delete_odd_positions() {
		if (!length)
			return;

		insert_front (-6871);	// Dummy head
		delete_even_positions();
		delete_front();
	}

	// bool is_palindrome() {	// I would say that is a bad code
	// 	if (length <= 1)
	// 		return true;
	// 	if (length == 2)
	// 		return head->data == tail->data;
	// 	Node* right_cur = tail;
	// 	Node* left_cur = head;
	// 	if (length % 2 == 0) {
	// 		do {
	// 			if (left_cur->data != right_cur->data)
	// 				return false;
	// 			right_cur = right_cur->prev;
	// 			left_cur = left_cur->next;
	// 		} while (left_cur ->next != right_cur || left_cur->prev != right_cur);
	// 	}
	// 	else {
	// 		while (left_cur != right_cur) {
	// 			if (left_cur->data != right_cur->data)
	// 				return false;
	// 			right_cur = right_cur->prev;
	// 			left_cur = left_cur->next;
	// 		}
	// 	}
	// 	return true;
	// }

	typedef Node* Lnode;
	bool is_palindrome() {
		if (length <= 1)
			return true;

		int len = length / 2;
		Lnode start{head}, end{tail};

		while(len--) {
			if(start->data != end->data)
				return false;
			start = start->next;
			end = end->prev;
		}
		return true;
	}

	// void find_the_middile() {
	// 	Node* fast_cur = head;
	// 	for (Node* cur = head; fast_cur ; fast_cur = fast_cur->next->next, cur = cur->next) {
	// 		if(fast_cur == tail){
	// 			cout <<cur->data;
	// 			break;
	// 		} else if(fast_cur->next->next == nullptr) {
	// 			cout<< cur->data << cur->next->data;
	// 			break;
	// 		}
	// 	}
	// }

	int find_middile1() {
		assert (head);
		Node *start_cur = head, *end_cur = tail;
		while (start_cur != end_cur && start_cur->next != end_cur) {
			start_cur = start_cur->next;
			end_cur = end_cur->prev;
		}
	return end_cur->data;
	}

	int find_middile2() {
		assert(head);

		Node* slow = head, *fast = head;

		while (fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow->data;
	}
	void swap_nodes(Node* node1, Node* node2) {

        Node* tempPrev = node1->prev;
        Node* tempNext = node1->next;

        if (node1->next == node2) {
            if (node1->prev) {
                node1->prev->next = node2;
            }
            if (node2->next) {
                node2->next->prev = node1;
            }
            node1->next = node2->next;
            node2->prev = node1->prev;
            node2->next = node1;
            node1->prev = node2;
        } else if (node2->next == node1) { 
            if (node2->prev) {
                node2->prev->next = node1;
            }
            if (node1->next) {
                node1->next->prev = node2;
            }
            node2->next = node1->next;
            node1->prev = node2->prev;
            node1->next = node2;
            node2->prev = node1;
        } else {
            if (node1->prev) {
                node1->prev->next = node2;
            }
            if (node1->next) {
                node1->next->prev = node2;
            }

            if (node2->prev) {
                node2->prev->next = node1;
            }
            if (node2->next) {
                node2->next->prev = node1;
            }

            node1->next = node2->next;
            node2->next = tempNext;

            node1->prev = node2->prev;
            node2->prev = tempPrev;
        }

        if (node1 == head && node2 == tail ||node1 == tail && node2 == head) {
            swap(head, tail);
        }
		debug_verify_data_integrity();
    }

	void swap_forward_with_backward(int k) {
		int j = k % length - 1;
		Node* start_cur = head;
		Node* end_cur = tail;

		while (j -- > 0) {
			debug_print_list();
			start_cur = start_cur->next;
			end_cur = end_cur->prev;
		}

		swap_nodes(start_cur, end_cur);

		debug_verify_data_integrity();
	}

	void reverse() {
		Node* cur = head;
		Node* temp_next {};
		Node* temp_prev {};
		while (cur) {
			temp_next = cur->next;
			temp_prev = cur->prev;

			cur->next = temp_prev;
			cur->prev = temp_next;

			cur = temp_next;;
		}
		Node* temp = head;
		head = tail;
		tail = temp;
		debug_print_list();
		debug_verify_data_integrity();
	}

	void merge_2sorted_lists(LinkedList &other) {
		if (!other.head) {
			return;
		}
		
		if (head) {
			Node* cur1 = head;
			Node* cur2 = other.head;
			Node* last { };
			head = nullptr;

			while (cur1 && cur2) {
				Node* next { };

				if (cur1->data <= cur2->data) {
					next = cur1;
					cur1 = cur1->next;
				} else {
					next = cur2;
					cur2 = cur2->next;
				}
				link(last, next);
				last = next;
				if (!head)
					head = last;
			}
			if (cur2) {
				tail = other.tail;
				link(last, cur2);
			} else if (cur1) {
				link(last, cur1);
			}
		} else {
			head = other.head;
			tail = other.tail;
		}
		length += other.length;
		debug_data.insert(debug_data.end(), other.debug_data.begin(), other.debug_data.end());
		other.head = other.tail = nullptr;
		other.length = 0;
		other.debug_data.clear();

		debug_verify_data_integrity();
	}
};