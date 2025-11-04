#pragma once
#include <cstdint>
#include <stdexcept>

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
    std::uint32_t m_count;
    
public:
    List() : head(nullptr), tail(nullptr), m_count(0) {}
    
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
        if ((tail == nullptr)) {
            head = (tail = newNode);
        } else {
            (tail->next) = newNode;
            (newNode->prev) = tail;
            tail = newNode;
        }
        ++m_count;
    }
    
    T pop() {
        if ((tail == nullptr)) {
            throw std::runtime_error("List is empty");
        }
        Node* temp = tail;
        T value = (temp->value);
        tail = (tail->prev);
        if ((tail != nullptr)) {
            (tail->next) = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        --m_count;
        return value;
    }
    
    T shift() {
        if ((head == nullptr)) {
            throw std::runtime_error("List is empty");
        }
        Node* temp = head;
        T value = (temp->value);
        head = (head->next);
        if ((head != nullptr)) {
            (head->prev) = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --m_count;
        return value;
    }
    
    void unshift(const T& value) {
        Node* newNode = new Node(value);
        if ((head == nullptr)) {
            head = (tail = newNode);
        } else {
            (newNode->next) = head;
            (head->prev) = newNode;
            head = newNode;
        }
        ++m_count;
    }
    
    std::uint32_t count() const {
        return m_count;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (((current->value) == value)) {
                if ((current->prev) != nullptr) {
                    ((current->prev)->next) = (current->next);
                } else {
                    head = (current->next);
                }
                if ((current->next) != nullptr) {
                    ((current->next)->prev) = (current->prev);
                } else {
                    tail = (current->prev);
                }
                delete current;
                --m_count;
                return true;
            }
            current = (current->next);
        }
        return false;
    }
};

}  // namespace linked_list
