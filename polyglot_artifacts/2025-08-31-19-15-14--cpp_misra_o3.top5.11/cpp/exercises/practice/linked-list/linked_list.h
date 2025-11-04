#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
    };

public:
    using size_type = std::uint32_t;
    List() noexcept : head_{nullptr}, tail_{nullptr}, size_{0U} {}

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
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
        Node* const new_node = new Node{value, tail_, nullptr};
        if (tail_ != nullptr) {
            tail_->next = new_node;
        } else {
            head_ = new_node;
        }
        tail_ = new_node;
        ++size_;
    }

    void unshift(const T& value) {
        Node* const new_node = new Node{value, nullptr, head_};
        if (head_ != nullptr) {
            head_->prev = new_node;
        } else {
            tail_ = new_node;
        }
        head_ = new_node;
        ++size_;
    }

    T pop() {
        if (size_ == 0U) {
            throw std::out_of_range{"pop on empty List"};
        }
        Node* const old_tail = tail_;
        T const ret_val = old_tail->value;
        tail_ = old_tail->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete old_tail;
        --size_;
        return ret_val;
    }

    T shift() {
        if (size_ == 0U) {
            throw std::out_of_range{"shift on empty List"};
        }
        Node* const old_head = head_;
        T const ret_val = old_head->value;
        head_ = old_head->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete old_head;
        --size_;
        return ret_val;
    }

    bool erase(const T& value) {
        Node* current = head_;
        while (current != nullptr) {
            if (current->value == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head_ = current->next;
                }

                if (current->next != nullptr) {
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

    [[nodiscard]] size_type count() const noexcept {
        return size_;
    }

private:
    void clear() noexcept {
        while (head_ != nullptr) {
            Node* const temp = head_;
            head_ = head_->next;
            delete temp;
        }
        tail_ = nullptr;
        size_ = 0U;
    }

    Node* head_;
    Node* tail_;
    size_type size_;
};

}  // namespace linked_list
