#pragma once

#include <cstddef>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push(const T& val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    T pop() {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        Node* temp = tail;
        T val = temp->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        size--;
        return val;
    }

    T shift() {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        Node* temp = head;
        T val = temp->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        size--;
        return val;
    }

    void unshift(const T& val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    size_t count() const {
        return size;
    }

    bool erase(const T& val) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == val) {
                if (current == head) {
                    Node* temp = head;
                    if (head == tail) {
                        head = tail = nullptr;
                    } else {
                        head = head->next;
                        head->prev = nullptr;
                    }
                    delete temp;
                    size--;
                } else if (current == tail) {
                    Node* temp = tail;
                    if (head == tail) {
                        head = tail = nullptr;
                    } else {
                        tail = tail->prev;
                        tail->next = nullptr;
                    }
                    delete temp;
                    size--;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    size--;
                }
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
