#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    List() noexcept;
    List(const List& other);
    List(List&& other) noexcept;
    ~List();

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    void push(const T& value);
    T pop();
    T shift();
    void unshift(const T& value);
    std::size_t count() const noexcept;

    bool erase(const T& value);

private:
    struct Node {
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        T value;
        Node* prev;
        Node* next;
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear() noexcept;
};

// Implementation

template <typename T>
List<T>::List() noexcept : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U)) {}

template <typename T>
List<T>::List(const List& other) : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U)) {
    Node* cur = other.head_;
    while (cur != nullptr) {
        this->push(cur->value);
        cur = cur->next;
    }
}

template <typename T>
List<T>::List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = static_cast<std::size_t>(0U);
}

template <typename T>
List<T>::~List() {
    this->clear();
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        List tmp(other);
        std::swap(this->head_, tmp.head_);
        std::swap(this->tail_, tmp.tail_);
        std::swap(this->size_, tmp.size_);
    }
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        this->clear();
        this->head_ = other.head_;
        this->tail_ = other.tail_;
        this->size_ = other.size_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }
    return *this;
}

template <typename T>
void List<T>::push(const T& value) {
    Node* node = new Node(value);
    if (this->tail_ == nullptr) {
        this->head_ = node;
        this->tail_ = node;
    } else {
        node->prev = this->tail_;
        this->tail_->next = node;
        this->tail_ = node;
    }
    this->size_ = this->size_ + static_cast<std::size_t>(1U);
}

template <typename T>
T List<T>::pop() {
    if (this->tail_ == nullptr) {
        throw std::out_of_range("pop on empty List");
    }
    Node* node = this->tail_;
    T value = std::move(node->value);

    if (node->prev != nullptr) {
        node->prev->next = nullptr;
        this->tail_ = node->prev;
    } else {
        this->head_ = nullptr;
        this->tail_ = nullptr;
    }
    delete node;
    this->size_ = this->size_ - static_cast<std::size_t>(1U);
    return value;
}

template <typename T>
T List<T>::shift() {
    if (this->head_ == nullptr) {
        throw std::out_of_range("shift on empty List");
    }
    Node* node = this->head_;
    T value = std::move(node->value);

    if (node->next != nullptr) {
        node->next->prev = nullptr;
        this->head_ = node->next;
    } else {
        this->head_ = nullptr;
        this->tail_ = nullptr;
    }
    delete node;
    this->size_ = this->size_ - static_cast<std::size_t>(1U);
    return value;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* node = new Node(value);
    if (this->head_ == nullptr) {
        this->head_ = node;
        this->tail_ = node;
    } else {
        node->next = this->head_;
        this->head_->prev = node;
        this->head_ = node;
    }
    this->size_ = this->size_ + static_cast<std::size_t>(1U);
}

template <typename T>
std::size_t List<T>::count() const noexcept {
    return this->size_;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* cur = this->head_;
    while (cur != nullptr) {
        if ((cur->value == value)) {
            Node* prev = cur->prev;
            Node* next = cur->next;

            if (prev != nullptr) {
                prev->next = next;
            } else {
                this->head_ = next;
            }

            if (next != nullptr) {
                next->prev = prev;
            } else {
                this->tail_ = prev;
            }

            delete cur;
            this->size_ = this->size_ - static_cast<std::size_t>(1U);
            return true;
        }
        cur = cur->next;
    }
    return false;
}

template <typename T>
void List<T>::clear() noexcept {
    Node* cur = this->head_;
    while (cur != nullptr) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = static_cast<std::size_t>(0U);
}

}  // namespace linked_list
