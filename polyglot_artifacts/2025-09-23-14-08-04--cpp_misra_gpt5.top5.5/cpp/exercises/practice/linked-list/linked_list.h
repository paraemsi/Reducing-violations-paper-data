#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List final {
public:
    List() noexcept = default;
    ~List() {
        clear_();
    }

    List(const List& other) {
        copy_from_(other);
    }

    List(List&& other) noexcept {
        move_from_(other);
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear_();
            copy_from_(other);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear_();
            move_from_(other);
        }
        return *this;
    }

    void push(const T& value) {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        ++count_;
    }

    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop from empty list");
        }
        Node* node = tail_;
        T value = node->value;
        tail_ = node->prev;
        if (tail_ == nullptr) {
            head_ = nullptr;
        } else {
            tail_->next = nullptr;
        }
        delete node;
        --count_;
        return value;
    }

    void unshift(const T& value) {
        Node* node = new Node(value);
        if (head_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++count_;
    }

    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("shift from empty list");
        }
        Node* node = head_;
        T value = node->value;
        head_ = node->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        } else {
            head_->prev = nullptr;
        }
        delete node;
        --count_;
        return value;
    }

    std::size_t count() const noexcept {
        return count_;
    }

    bool erase(const T& value) {
        Node* current = head_;
        while (current != nullptr) {
            if (current->value == value) {
                Node* prev = current->prev;
                Node* next = current->next;

                if (prev == nullptr) {
                    head_ = next;
                } else {
                    prev->next = next;
                }

                if (next == nullptr) {
                    tail_ = prev;
                } else {
                    next->prev = prev;
                }

                delete current;
                --count_;
                return true;
            }
            current = current->next;
        }
        return false;
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        T value;
        Node* prev;
        Node* next;
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t count_ = 0U;

    void clear_() noexcept {
        Node* cur = head_;
        while (cur != nullptr) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head_ = nullptr;
        tail_ = nullptr;
        count_ = 0U;
    }

    void copy_from_(const List& other) {
        head_ = nullptr;
        tail_ = nullptr;
        count_ = 0U;
        Node* cur = other.head_;
        while (cur != nullptr) {
            push(cur->value);
            cur = cur->next;
        }
    }

    void move_from_(List& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        count_ = other.count_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.count_ = 0U;
    }
};

}  // namespace linked_list
