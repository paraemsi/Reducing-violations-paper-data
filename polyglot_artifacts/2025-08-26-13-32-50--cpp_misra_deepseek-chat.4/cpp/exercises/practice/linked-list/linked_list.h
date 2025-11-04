#pragma once
#include <cstdint>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    std::uint32_t list_size;
    
public:
    List() : head(nullptr), tail(nullptr), list_size(0U) {}
    
    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* const next = current->next;
            delete current;
            current = next;
        }
    }
    
    void push(const T& value) {
        Node* const new_node = new Node(value);
        if (tail == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        ++list_size;
    }
    
    T pop() {
        if (tail == nullptr) {
            return T();
        }
        Node* const temp = tail;
        T data = temp->data;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        --list_size;
        return data;
    }
    
    T shift() {
        if (head == nullptr) {
            return T();
        }
        Node* const temp = head;
        T data = temp->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --list_size;
        return data;
    }
    
    void unshift(const T& value) {
        Node* const new_node = new Node(value);
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        ++list_size;
    }
    
    std::uint32_t count() const {
        return list_size;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if ((current->data) == value) {
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
