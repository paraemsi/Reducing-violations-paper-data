#pragma once

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
            // According to the note, we might want to raise an exception
            // For now, we'll just return a default value
            return T();
        }
        Node* temp = tail;
        T value = temp->value;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        num_elements--;
        return value;
    }
    
    T shift() {
        if (head == nullptr) {
            // According to the note, we might want to raise an exception
            // For now, we'll just return a default value
            return T();
        }
        Node* temp = head;
        T value = temp->value;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
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
            if (current->value == value) {
                // Found the node to erase
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
                num_elements--;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
