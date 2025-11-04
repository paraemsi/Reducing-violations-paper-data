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
    int num_elements;
    
public:
    List() : head(nullptr), tail(nullptr), num_elements(0) {}
    
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
        ++num_elements;
    }
    
    T pop() {
        if (!tail) {
            throw std::runtime_error("Cannot pop from an empty list");
        }
        Node* temp = tail;
        T data = temp->data;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        --num_elements;
        return data;
    }
    
    T shift() {
        if (!head) {
            throw std::runtime_error("Cannot shift from an empty list");
        }
        Node* temp = head;
        T data = temp->data;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --num_elements;
        return data;
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
        ++num_elements;
    }
    
    int count() const {
        return num_elements;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
                --num_elements;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
