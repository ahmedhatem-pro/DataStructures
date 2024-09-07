#include <iostream>
#include <cassert>
using namespace std;

struct ColumnNode {
    int data { };
    int column { };
    ColumnNode* next { };
    ColumnNode* prev { };

    ColumnNode(int data, int column) : data(data), column(column) { }
};


class ColumnLinkedList {
private:
    ColumnNode *head { };
    ColumnNode *tail { };
    int length = 0;
    int cols { };

    
    void link(ColumnNode* first, ColumnNode* second) {
        if (first) {
            first->next = second;
        }
        if (second) {
            second->prev = first;
        }
    }

    ColumnNode* embed_after(ColumnNode* node_before, int data, int col) {
        ColumnNode* middle = new ColumnNode(data, col);
        ++length;

        ColumnNode* node_after = node_before->next;
        link(node_before, middle);
        
        if (!node_after) {
            tail = middle;
        }
        else
            link(middle, node_after);
        
        return middle;
    }

    ColumnNode* get_col(int col, bool is_create_if_missing) {
        ColumnNode* prev_col = head;
        while (prev_col->next && prev_col->next->column < col) {
            prev_col = prev_col->next;
        }
        bool found = prev_col->next && prev_col->next->column == col;

        if (found) {
            return prev_col->next;
        }
        if (!is_create_if_missing) {
            return nullptr;
        }
        return embed_after(prev_col, 0, col);
    }
public:
    ColumnLinkedList(int cols) : cols(cols) {
        tail = head = new ColumnNode(0, -1);
        ++length;
    }

    void print_row() {
        ColumnNode* cur = head->next;

        for (int c = 0; c < cols; c++) {
            if (cur && cur->column == c) {
                cout << cur->data << " ";
                cur = cur->next;
            } else 
                cout << "0 ";
        }
        cout << "\n";
    }

    void print_row_nonzer() {
        for (ColumnNode* cur = head->next; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    void set_value(int data, int col) {
        get_col(col, true)->data = data;
    }

    int get_value(int col){
        ColumnNode* node = get_col(col, false);
        if (!node)
            return 0;
        return node->data;
    }

    void add(ColumnLinkedList &other) {
        assert(cols == other.cols);

        for (ColumnNode* other_cur = other.head->next; other_cur; other_cur= other_cur->next) {
            ColumnNode* this_col = get_col(other_cur->column, true);
            this_col->data += other_cur->data;
        }
        // The same as the sparse array
    }
};

    struct RowNode {
        int row { };
        ColumnLinkedList col_list;
        RowNode* next { };
        RowNode* prev { };

        RowNode(int row, int cols) : row(row), col_list(cols) { }
    };

class SparseMatrix {
private:
    RowNode *head { };
    RowNode *tail { };
    int length = 0;
    int rows { };
    int cols { };

    void link(RowNode* first, RowNode* second) {
        if (first) {
            first->next = second;
        }
        if (second) {
            second->prev = first;
        }
    }

    RowNode* embed_after(RowNode* node_before, int data, int row) {
        RowNode* middle = new RowNode(data, row);
        ++length;

        RowNode* node_after = node_before->next;
        link(node_before, middle);
        
        if (!node_after) {
            tail = middle;
        }
        else
            link(middle, node_after);
        
        return middle;
    }

    RowNode* get_row(int row, bool is_create_if_missing) {
        RowNode* prev_row = head;
        while (prev_row->next && prev_row->next->row < row) {
            prev_row = prev_row->next;
        }
        bool found = prev_row->next && prev_row->next->row == row;

        if (found) {
            return prev_row->next;
        }
        if (!is_create_if_missing) {
            return nullptr;
        }
        return embed_after(prev_row, 0, row);
    }
public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols){
        tail = head = new RowNode(-1, cols);
        length++;
    }

    void set_value(int data, int row, int col) {
        assert(0 <= row && row < rows);
        assert(0 <= col && col < cols);
    
        RowNode* node = get_row(row, true);
        node->col_list.set_value(data, col);
    }

    int get_value(int row, int col) {
        assert(0 <= row && row < rows);
        assert(0 <= col && col < cols);

        RowNode* node = get_row(row, false);
        if(!node)
            return 0;
        return node->col_list.get_value(col);
    }

    void print_matrix() {
        cout<< "\nPrint Matrix: "<< rows << " x " << cols << "\n";
        RowNode* cur = head->next;
        for (int r = 0; r < rows; r++) {
            if (cur && cur->row == r) {
                cur->col_list.print_row();
                cur = cur->next;
            }else {
                for (int j = 0; j < cols; j++)
                    cout << "0 ";
                cout << "\n";
            }
        }
    }

    void print_matrix_nonzero() {
        cout<< "\nPrint Matrix: "<< rows << " x " << cols << "\n";
        for (RowNode* cur = head->next; cur; cur = cur->next)
            cur->col_list.print_row_nonzer();
    }

    void add(SparseMatrix &other) {
        assert(rows == other.rows && cols == other.cols);

        for (RowNode* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
            RowNode* this_row = get_row(other_cur->row, true);
            this_row->col_list.add(other_cur->col_list);
        }
    }
};
