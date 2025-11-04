#pragma once
#include <cstddef>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    std::size_t list_size;
    
public:
    List() : head(nullptr), tail(nullptr), list_size(0) {}
    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
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
        ++list_size;
    }
    
    T pop() {
        if (tail == nullptr) {
            throw "List is empty";
        }
        Node* temp = tail;
        T value = temp->value;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        --list_size;
        return value;
    }
    
    T shift() {
        if (head == nullptr) {
            throw "List is empty";
        }
        Node* temp = head;
        T value = temp->value;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --list_size;
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
        ++list_size;
    }
    
    std::size_t count() const {
        return list_size;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
                --list_size;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
