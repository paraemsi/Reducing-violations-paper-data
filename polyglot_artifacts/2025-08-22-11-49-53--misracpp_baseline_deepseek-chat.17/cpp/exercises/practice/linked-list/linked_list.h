#pragma once

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int num_elements;
    
public:
    List() : head(nullptr), tail(nullptr), num_elements(0) {}
    
    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    void push(const T& value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        num_elements++;
    }
    
    T pop() {
        if (tail == nullptr) {
            throw "Cannot pop from empty list";
        }
        Node* last_node = tail;
        T value = last_node->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete last_node;
        num_elements--;
        return value;
    }
    
    T shift() {
        if (head == nullptr) {
            throw "Cannot shift from empty list";
        }
        Node* first_node = head;
        T value = first_node->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete first_node;
        num_elements--;
        return value;
    }
    
    void unshift(const T& value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        num_elements++;
    }
    
    int count() const {
        return num_elements;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                // Update previous node's next pointer
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                // Update next node's prev pointer
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
                num_elements--;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
