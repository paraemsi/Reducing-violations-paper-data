#pragma once
#include <stdexcept>
#include <cstddef>

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
    std::size_t size;
    
public:
    // Constructor
    List() : head(nullptr), tail(nullptr), size(0) {}
    
    // Destructor
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
    
    // Assignment operator
    List& operator=(const List& other) {
        if (this != &other) {
            // Clear current list
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            head = nullptr;
            tail = nullptr;
            size = 0;
            
            // Copy from other list
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
            // Empty list
            head = tail = newNode;
        } else {
            // Non-empty list
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    
    // Remove and return the last element
    T pop() {
        if (tail == nullptr) {
            throw std::runtime_error("Cannot pop from empty list");
        }
        
        T value = tail->data;
        Node* temp = tail;
        
        if (head == tail) {
            // Only one element
            head = tail = nullptr;
        } else {
            // Multiple elements
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        delete temp;
        size--;
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
            // Only one element
            head = tail = nullptr;
        } else {
            // Multiple elements
            head = head->next;
            head->prev = nullptr;
        }
        
        delete temp;
        size--;
        return value;
    }
    
    // Add element to the start of the list
    void unshift(const T& value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            // Empty list
            head = tail = newNode;
        } else {
            // Non-empty list
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    
    // Return the total number of elements
    std::size_t count() const {
        return size;
    }
    
    // Remove the first occurrence of a value
    bool erase(const T& value) {
        Node* current = head;
        
        while (current != nullptr) {
            if (current->data == value) {
                // Found the node to delete
                if (current == head && current == tail) {
                    // Only node in the list
                    head = tail = nullptr;
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
                size--;
                return true;
            }
            current = current->next;
        }
        
        return false;  // Value not found
    }
};

}  // namespace linked_list
