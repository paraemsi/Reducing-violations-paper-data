#pragma once

#include <cstddef>     // std::size_t
#include <stdexcept>   // std::out_of_range
#include <utility>     // std::move, std::forward

namespace linked_list {

// Doubly-linked list implementation.
// All code is header-only so the template can be instantiated
// for any user supplied type without separate compilation.
template <typename T>
class List {
private:
    struct Node {
        T       value;
        Node*   prev{nullptr};
        Node*   next{nullptr};

        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v)      : value(std::move(v)) {}
        ~Node() = default;
    };

    Node*   head_{nullptr};
    Node*   tail_{nullptr};
    std::size_t size_{0};

    void clear() noexcept {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0;
    }

public:
    // Constructors / assignment
    List()  = default;
    ~List() { clear(); }

    List(const List&)            = delete;
    List& operator=(const List&) = delete;
    // Move constructor performs pointer transfer without deep copy.
    List(List&& other) noexcept
        : head_(other.head_)
        , tail_(other.tail_)
        , size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // Adds an element to the end of the list.
    void push(const T& value) { emplace_back(value); }
    void push(T&& value)      { emplace_back(std::move(value)); }

    // Removes and returns the last element.
    T pop() {
        if (empty()) {
            throw std::out_of_range("List::pop on empty list");
        }
        Node* tmp = tail_;
        T out = std::move(tmp->value);

        tail_ = tail_->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;    // list became empty
        }
        delete tmp;
        --size_;
        return out;
    }

    // Removes and returns the first element.
    T shift() {
        if (empty()) {
            throw std::out_of_range("List::shift on empty list");
        }
        Node* tmp = head_;
        T out = std::move(tmp->value);

        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;    // list became empty
        }
        delete tmp;
        --size_;
        return out;
    }

    // Adds an element to the start of the list.
    void unshift(const T& value) { emplace_front(value); }
    void unshift(T&& value)      { emplace_front(std::move(value)); }

    // Returns the number of elements in the list.
    std::size_t count() const noexcept { return size_; }

    // Removes the first occurrence of `value` from the list.
    // Returns true if an element was removed, false otherwise.
    bool erase(const T& value) {
        for (Node* cur = head_; cur; cur = cur->next) {
            if (cur->value == value) {
                if (cur->prev) {
                    cur->prev->next = cur->next;
                } else {            // removing head
                    head_ = cur->next;
                }
                if (cur->next) {
                    cur->next->prev = cur->prev;
                } else {            // removing tail
                    tail_ = cur->prev;
                }
                delete cur;
                --size_;
                return true;
            }
        }
        return false;
    }

    bool empty() const noexcept { return size_ == 0; }

private:
    template <typename U>
    void emplace_back(U&& value) {
        Node* node = new Node(std::forward<U>(value));
        node->prev = tail_;
        if (tail_) tail_->next = node;
        tail_ = node;
        if (!head_) head_ = node;
        ++size_;
    }

    template <typename U>
    void emplace_front(U&& value) {
        Node* node = new Node(std::forward<U>(value));
        node->next = head_;
        if (head_) head_->prev = node;
        head_ = node;
        if (!tail_) tail_ = node;
        ++size_;
    }
};

}  // namespace linked_list
