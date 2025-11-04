#pragma once

#include <cstddef>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
public:
    List();
    ~List();

    void push(const T& value);
    T pop();
    void unshift(const T& value);
    T shift();
    std::size_t count() const;
    bool erase(const T& value);

private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;
};

// Implementation

template <typename T>
List<T>::List() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
List<T>::~List() {
    while (head_) {
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

template <typename T>
void List<T>::push(const T& value) {
    Node* node = new Node(value);
    if (!tail_) {
        head_ = tail_ = node;
    } else {
        tail_->next = node;
        node->prev = tail_;
        tail_ = node;
    }
    ++size_;
}

template <typename T>
T List<T>::pop() {
    if (!tail_) {
        throw std::out_of_range("pop from empty list");
    }
    Node* node = tail_;
    T val = node->value;
    tail_ = tail_->prev;
    if (tail_) {
        tail_->next = nullptr;
    } else {
        head_ = nullptr;
    }
    delete node;
    --size_;
    return val;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* node = new Node(value);
    if (!head_) {
        head_ = tail_ = node;
    } else {
        node->next = head_;
        head_->prev = node;
        head_ = node;
    }
    ++size_;
}

template <typename T>
T List<T>::shift() {
    if (!head_) {
        throw std::out_of_range("shift from empty list");
    }
    Node* node = head_;
    T val = node->value;
    head_ = head_->next;
    if (head_) {
        head_->prev = nullptr;
    } else {
        tail_ = nullptr;
    }
    delete node;
    --size_;
    return val;
}

template <typename T>
std::size_t List<T>::count() const {
    return size_;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* curr = head_;
    while (curr) {
        if (curr->value == value) {
            if (curr->prev) {
                curr->prev->next = curr->next;
            } else {
                head_ = curr->next;
            }
            if (curr->next) {
                curr->next->prev = curr->prev;
            } else {
                tail_ = curr->prev;
            }
            delete curr;
            --size_;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

}  // namespace linked_list
