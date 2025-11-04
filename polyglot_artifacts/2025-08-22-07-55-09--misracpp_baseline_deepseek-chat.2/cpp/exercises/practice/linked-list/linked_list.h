#pragma once
#include <stdexcept>

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
    int list_size;
    
public:
    List() : head(nullptr), tail(nullptr), list_size(0) {}
    
    ~List() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void push(const T& value) {
        Node* new_node = new Node(value);
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        list_size++;
    }
    
    T pop() {
        if (!tail) {
            throw std::runtime_error("Cannot pop from empty list");
        }
        Node* temp = tail;
        T value = temp->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        list_size--;
        return value;
    }
    
    T shift() {
        if (!head) {
            throw std::runtime_error("Cannot shift from empty list");
        }
        Node* temp = head;
        T value = temp->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        list_size--;
        return value;
    }
    
    void unshift(const T& value) {
        Node* new_node = new Node(value);
        if (!head) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        list_size++;
    }
    
    int count() const {
        return list_size;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                // Adjust surrounding pointers
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    // This is the head node
                    head = current->next;
                    if (head) head->prev = nullptr;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    // This is the tail node
                    tail = current->prev;
                    if (tail) tail->next = nullptr;
                }
                // Delete the node and update size
                delete current;
                list_size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
