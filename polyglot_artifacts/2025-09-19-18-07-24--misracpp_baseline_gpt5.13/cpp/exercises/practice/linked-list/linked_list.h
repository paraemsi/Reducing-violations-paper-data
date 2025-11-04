#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    List() = default;

    // Rule of Five
    ~List() { clear(); }

    List(const List& other) {
        for (Node* n = other.head_; n != nullptr; n = n->next) {
            push(n->value);
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* n = other.head_; n != nullptr; n = n->next) {
                push(n->value);
            }
        }
        return return_self();
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return return_self();
    }

    // Adds an element to the end of the list
    void push(const T& value) {
        Node* node = new Node(value);
        link_back(node);
    }

    void push(T&& value) {
        Node* node = new Node(std::move(value));
        link_back(node);
    }

    // Removes and returns the last element of the list
    T pop() {
        if (size_ == 0) {
            throw std::out_of_range("pop from empty List");
        }
        Node* node = tail_;
        T out = std::move(node->value);

        tail_ = node->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete node;
        --size_;
        return out;
    }

    // Removes and returns the first element of the list
    T shift() {
        if (size_ == 0) {
            throw std::out_of_range("shift from empty List");
        }
        Node* node = head_;
        T out = std::move(node->value);

        head_ = node->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete node;
        --size_;
        return out;
    }

    // Adds an element to the start of the list
    void unshift(const T& value) {
        Node* node = new Node(value);
        link_front(node);
    }

    void unshift(T&& value) {
        Node* node = new Node(std::move(value));
        link_front(node);
    }

    // Returns the number of elements in the list
    std::size_t count() const noexcept { return size_; }

    // Removes the first occurrence of 'value' from the list, returns true if removed
    bool erase(const T& value) {
        for (Node* n = head_; n != nullptr; n = n->next) {
            if (n->value == value) {
                if (n->prev != nullptr) {
                    n->prev->next = n->next;
                } else {
                    head_ = n->next;
                }
                if (n->next != nullptr) {
                    n->next->prev = n->prev;
                } else {
                    tail_ = n->prev;
                }
                delete n;
                --size_;
                return true;
            }
        }
        return false;
    }

private:
    struct Node {
        T value;
        Node* prev{nullptr};
        Node* next{nullptr};

        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v) : value(std::move(v)) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    void clear() noexcept {
        Node* n = head_;
        while (n != nullptr) {
            Node* next = n->next;
            delete n;
            n = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    void link_back(Node* node) {
        node->prev = tail_;
        node->next = nullptr;
        if (tail_ != nullptr) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        ++size_;
    }

    void link_front(Node* node) {
        node->next = head_;
        node->prev = nullptr;
        if (head_ != nullptr) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        ++size_;
    }

    // Helper to satisfy -Weffc++ complaining about returning *this by reference in templated context
    List& return_self() { return *this; }
};

}  // namespace linked_list
