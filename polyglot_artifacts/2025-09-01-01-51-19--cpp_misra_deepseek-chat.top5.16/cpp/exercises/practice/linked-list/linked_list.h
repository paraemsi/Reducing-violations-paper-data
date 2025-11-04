#pragma once
#include <cstdint>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
        Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    std::int32_t size_;
    
public:
    List() : head(nullptr), tail(nullptr), size_(0) {}
    
    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    void push(const T& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size_++;
    }
    
    T pop() {
        if (tail == nullptr) {
            // Since we can't change the function signature, and the tests may expect certain behavior
            // We need to handle this. Let's throw an exception if the list is empty
            throw "Cannot pop from empty list";
        }
        T value = tail->value;
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        size_--;
        return value;
    }
    
    T shift() {
        if (head == nullptr) {
            throw "Cannot shift from empty list";
        }
        T value = head->value;
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        size_--;
        return value;
    }
    
    void unshift(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size_++;
    }
    
    std::int32_t count() const {
        return size_;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                if (current == head) {
                    // Use shift() to remove the head
                    // We need to capture the result to avoid warnings, but we don't need it
                    static_cast<void>(shift());
                } else if (current == tail) {
                    // Use pop() to remove the tail
                    static_cast<void>(pop());
                } else {
                    // Update pointers
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    size_--;
                }
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
