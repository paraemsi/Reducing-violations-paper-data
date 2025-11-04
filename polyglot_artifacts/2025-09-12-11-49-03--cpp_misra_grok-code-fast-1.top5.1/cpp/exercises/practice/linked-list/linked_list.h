#pragma once

#include <cstdint>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() {
        while ((head != nullptr)) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(T value) {
        Node* newNode = new Node(value);
        if ((tail == nullptr)) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

    T pop() {
        if ((head == nullptr)) {
            throw std::out_of_range("List is empty");
        }
        T value = tail->data;
        Node* temp = tail;
        if ((head == tail)) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        --size;
        return value;
    }

    void unshift(T value) {
        Node* newNode = new Node(value);
        if ((head == nullptr)) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++size;
    }

    T shift() {
        if ((head == nullptr)) {
            throw std::out_of_range("List is empty");
        }
        T value = head->data;
        Node* temp = head;
        if ((head == tail)) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        --size;
        return value;
    }

    std::size_t count() const {
        return size;
    }

    bool erase(T value) {
        Node* current = head;
        while ((current != nullptr)) {
            if ((current->data == value)) {
                if ((current == head)) {
                    shift();
                } else if ((current == tail)) {
                    pop();
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    --size;
                }
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
