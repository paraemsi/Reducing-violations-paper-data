#pragma once
#include <cstdint>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        explicit Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    std::uint32_t size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    
    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Copy constructor
    List(const List& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }
    
    // Copy assignment operator
    List& operator=(const List& other) {
        if (this != &other) {
            // Clear existing list
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            head = nullptr;
            tail = nullptr;
            size = 0;
            
            // Copy from other
            Node* current = other.head;
            while (current != nullptr) {
                push(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    // Add element to the end of the list
    void push(const T& value) {
        Node* newNode = new Node(value);
        
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size = size + 1;
    }
    
    // Remove and return the last element
    T pop() {
        if (tail == nullptr) {
            throw std::runtime_error("Cannot pop from empty list");
        }
        
        T value = tail->data;
        Node* temp = tail;
        
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        delete temp;
        size = size - 1;
        return value;
    }
    
    // Remove and return the first element
    T shift() {
        if (head == nullptr) {
            throw std::runtime_error("Cannot shift from empty list");
        }
        
        T value = head->data;
        Node* temp = head;
        
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        delete temp;
        size = size - 1;
        return value;
    }
    
    // Add element to the start of the list
    void unshift(const T& value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size = size + 1;
    }
    
    // Return the total number of elements
    std::uint32_t count() const {
        return size;
    }
    
    // Remove first occurrence of value, return true if deleted
    bool erase(const T& value) {
        Node* current = head;
        
        while (current != nullptr) {
            if (current->data == value) {
                // Handle removal of the found node
                if ((current == head) && (current == tail)) {
                    // Only node in list
                    head = nullptr;
                    tail = nullptr;
                } else if (current == head) {
                    // First node
                    head = current->next;
                    head->prev = nullptr;
                } else if (current == tail) {
                    // Last node
                    tail = current->prev;
                    tail->next = nullptr;
                } else {
                    // Middle node
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                
                delete current;
                size = size - 1;
                return true;
            }
            current = current->next;
        }
        
        return false;
    }
};

}  // namespace linked_list
