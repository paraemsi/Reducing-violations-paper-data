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
    List& operator=(const List& other) {
        if (this != &other) {
            List temp(other);
            swap(temp);
        }
        return *this;
    }

    List(List&& other) noexcept { move_from(std::move(other)); }
    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            move_from(std::move(other));
        }
        return *this;
    }

    void push(const T& value) {
        Node* n = new Node(value);
        append_node(n);
    }
    void push(T&& value) {
        Node* n = new Node(std::move(value));
        append_node(n);
    }

    T pop() {
        if (!tail_) throw std::out_of_range("pop from empty list");
        Node* n = tail_;
        T value = std::move(n->value);
        remove_node(n);
        return value;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        prepend_node(n);
    }
    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
        prepend_node(n);
    }

    T shift() {
        if (!head_) throw std::out_of_range("shift from empty list");
        Node* n = head_;
        T value = std::move(n->value);
        remove_node(n);
        return value;
    }

    std::size_t count() const noexcept { return size_; }

    bool erase(const T& value) {
        Node* current = head_;
        while (current) {
            if (current->value == value) {
                remove_node(current);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool empty() const noexcept { return size_ == 0; }

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

    void append_node(Node* n) {
        n->prev = tail_;
        n->next = nullptr;
        if (tail_) {
            tail_->next = n;
        } else {
            head_ = n;
        }
        tail_ = n;
        ++size_;
    }

    void prepend_node(Node* n) {
        n->next = head_;
        n->prev = nullptr;
        if (head_) {
            head_->prev = n;
        } else {
            tail_ = n;
        }
        head_ = n;
        ++size_;
    }

    void remove_node(Node* n) {
        Node* prev = n->prev;
        Node* next = n->next;
        if (prev) {
            prev->next = next;
        } else {
            head_ = next;
        }
        if (next) {
            next->prev = prev;
        } else {
            tail_ = prev;
        }
        delete n;
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
            push(cur->value);
            cur = cur->next;
        }
    }

    void move_from(List&& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    void swap(List& other) noexcept {
        using std::swap;
        swap(head_, other.head_);
        swap(tail_, other.tail_);
        swap(size_, other.size_);
    }
};

}  // namespace linked_list
