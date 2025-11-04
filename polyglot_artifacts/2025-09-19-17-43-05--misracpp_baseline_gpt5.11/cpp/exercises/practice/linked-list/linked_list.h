#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    List() = default;
    ~List() { clear(); }

    List(const List& other) { copy_from(other); }
    List(List&& other) noexcept { move_from(other); }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            move_from(other);
        }
        return *this;
    }

    void push(const T& value) { append_node(new Node(value)); }
    void push(T&& value) { append_node(new Node(std::move(value))); }

    T pop() {
        if (empty()) {
            throw std::out_of_range("List::pop on empty list");
        }
        return remove_tail();
    }

    void unshift(const T& value) { prepend_node(new Node(value)); }
    void unshift(T&& value) { prepend_node(new Node(std::move(value))); }

    T shift() {
        if (empty()) {
            throw std::out_of_range("List::shift on empty list");
        }
        return remove_head();
    }

    std::size_t count() const noexcept { return size_; }

    bool erase(const T& value) {
        Node* cur = head_;
        while (cur) {
            if (cur->value == value) {
                unlink_and_delete(cur);
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v) : value(std::move(v)) {}
        T value;
        Node* prev{nullptr};
        Node* next{nullptr};
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    bool empty() const noexcept { return size_ == 0; }

    void append_node(Node* node) {
        node->prev = tail_;
        node->next = nullptr;
        if (tail_) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        ++size_;
    }

    void prepend_node(Node* node) {
        node->next = head_;
        node->prev = nullptr;
        if (head_) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        ++size_;
    }

    T remove_head() {
        Node* node = head_;
        Node* next = node->next;
        if (next) {
            next->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        head_ = next;
        T value = std::move(node->value);
        delete node;
        --size_;
        return value;
    }

    T remove_tail() {
        Node* node = tail_;
        Node* prev = node->prev;
        if (prev) {
            prev->next = nullptr;
        } else {
            head_ = nullptr;
        }
        tail_ = prev;
        T value = std::move(node->value);
        delete node;
        --size_;
        return value;
    }

    void unlink_and_delete(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;
        if (prev) prev->next = next; else head_ = next;
        if (next) next->prev = prev; else tail_ = prev;
        delete node;
        --size_;
    }

    void clear() noexcept {
        Node* cur = head_;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    void copy_from(const List& other) {
        Node* cur = other.head_;
        while (cur) {
            append_node(new Node(cur->value));
            cur = cur->next;
        }
    }

    void move_from(List& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }
};

}  // namespace linked_list
