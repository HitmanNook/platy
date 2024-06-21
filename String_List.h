// Student ID: 20607502
// TODO - Type in your student ID after the colon above.
// String_List.h
//
#ifndef String_List_h
#define String_List_h

#include <iostream>
#include <sstream>

// Important implementation note: With the exception of to_string(),
// find*() and clear(), all list methods below should operate in a constant amount
// of time regardless of the size of the String_List instance.
//
// The semantics of _prev_to_current is such that it always points to the
// node *BEFORE* the current one. This makes the manipulations easy because
// we can only look forward (and not back) in singly linked lists.
//
// I've included some method header comments below where there's likely to
// be confusion.
//
class String_List {
private:
    struct Node {
        std::string data;
        Node *next;

        Node(std::string s = "") : data(s), next(nullptr) {}
    };

    Node *_head, *_tail, *_prev_to_current;
    size_t _size;

public:
    String_List() {
        Node *sentinel = new Node("_SENTINEL_");
        _head = sentinel;
        _tail = sentinel;
        _prev_to_current = sentinel;
        _size = 0;
    }

    ~String_List() {
        Node *curr = _head->next;
        for (size_t i = 0; i < _size; ++i) {
            Node *next = curr->next;
            free(curr);
            curr = next;
        }
    }

    String_List *insert_at_current(std::string s) {
        Node *temp = new Node(s);
        temp->next = _prev_to_current->next;
        _prev_to_current->next = temp;
        _size++;
        if(_prev_to_current == _tail){
            _tail = _prev_to_current->next;
        }
        return this;
    }

    String_List *push_back(std::string s) {
        Node *saved = _prev_to_current;
        _prev_to_current = _tail;
        insert_at_current(s);
        _tail = _prev_to_current->next;
        _prev_to_current = saved;
        return this;
    }

    String_List *push_front(std::string s) {
        Node *saved = _prev_to_current;
        _prev_to_current = _head;
        insert_at_current(s);
        _head->next = _prev_to_current->next;
        _prev_to_current = saved;
        return this;
    }

    String_List *advance_current() {
        if (_prev_to_current == _tail) return nullptr;
        _prev_to_current = _prev_to_current->next;
        return this;
    }

    std::string get_current() const {
        if (_prev_to_current->next == nullptr) return _head->data;
        return _prev_to_current->next->data;
    }

    String_List *remove_at_current() {
        Node *rem = _prev_to_current->next;
        if (rem == _tail) {
            _tail = _prev_to_current;
        }
        _prev_to_current->next = rem->next;
        free(rem);
        _size--;
        return this;
    }

    size_t get_size() const {
        return _size;
    }

    String_List *rewind() {
        _prev_to_current = _head;
        return this;
    }

    void clear() {
        Node *curr = _head->next;
        for (size_t i = 0; i < _size; ++i) {
            Node *next = curr->next;
            free(curr);
            curr = next;
        }
        _tail = _head;
        _prev_to_current = _head;
        _head->next = nullptr;
        _size = 0;
    }

    // Find a specific item. Does NOT change cursor.
    //
    // The following returns a reference to the target string if found. But what will
    // you do if you didn't find the requested string? Using sentinel markers is
    // one way to handle that situation. Usually there's only one copy of the
    // sentinel that's global. We will use a local one so it's cleaner with a
    // little more risk (what's the risk?)
    //
    std::string &find_item(std::string s) const {
        Node *curr = _head->next;
        for (size_t i = 0; i < _size; ++i) {
            Node *next = curr->next;
            if (curr->data == s) return curr->data;
            curr = next;
        }
        return _head->data;
    }

    // Print up to max_lines lines starting at _prev_to_current->next. If the caller
    // wants to print from the beginning of the list, they should rewind() it first.
    //
    std::string to_string() const {
        std::string ret = "# String_List - " + std::to_string(_size) + " entries total. Starting at cursor:\n";
        int counter = 0;
        Node *curr = _prev_to_current->next;
        while (curr != _tail) {
            Node *next = curr->next;
            ret += curr->data;
            ret += "\n";
            counter++;
            if (counter == 25) {
                ret += "...\n";
                return ret;
            }
            curr = next;
        }
        return ret + "\n";
    }
    friend class Tests; // Don't remove this line
};

#endif /* String_List_h */