#pragma once

#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T       value;
        Node*   next;
        Node*   prev;

        explicit Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node*         head_;
    Node*         tail_;
    std::uint32_t size_;

public:
    List() noexcept : head_(nullptr), tail_(nullptr), size_(0U) {}

    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept {
        if ((this != &other)) {
            clear();
            head_      = other.head_;
            tail_      = other.tail_;
            size_      = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    ~List() noexcept {
        clear();
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        if ((head_ == nullptr)) {
            head_ = newNode;
            tail_ = newNode;
        } else {
            newNode->prev = tail_;
            tail_->next   = newNode;
            tail_         = newNode;
        }
        ++size_;
    }

    T pop() {
        if ((size_ == 0U)) {
            throw std::out_of_range("pop on empty list");
        }

        Node* toRemove = tail_;
        T     retVal   = toRemove->value;

        tail_ = tail_->prev;
        if ((tail_ != nullptr)) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete toRemove;
        --size_;
        return retVal;
    }

    void unshift(const T& value) {
        Node* newNode = new Node(value);
        if ((head_ == nullptr)) {
            head_ = newNode;
            tail_ = newNode;
        } else {
            newNode->next = head_;
            head_->prev   = newNode;
            head_         = newNode;
        }
        ++size_;
    }

    T shift() {
        if ((size_ == 0U)) {
            throw std::out_of_range("shift on empty list");
        }

        Node* toRemove = head_;
        T     retVal   = toRemove->value;

        head_ = head_->next;
        if ((head_ != nullptr)) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete toRemove;
        --size_;
        return retVal;
    }

    std::uint32_t count() const noexcept {
        return size_;
    }

    bool erase(const T& value) {
        Node* current = head_;
        while (current != nullptr) {
            if ((current->value == value)) {
                if ((current->prev != nullptr)) {
                    current->prev->next = current->next;
                } else {
                    head_ = current->next;
                }

                if ((current->next != nullptr)) {
                    current->next->prev = current->prev;
                } else {
                    tail_ = current->prev;
                }

                delete current;
                --size_;
                return true;
            }
            current = current->next;
        }
        return false;
    }

private:
    void clear() noexcept {
        Node* current = head_;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }
};

}  // namespace linked_list
