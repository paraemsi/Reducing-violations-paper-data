#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:
    // Forward declaration of the internal node structure
    struct Node;

public:
    List() noexcept : head_{nullptr}, tail_{nullptr}, size_{0U} {}

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept : head_{other.head_}, tail_{other.tail_},
                                  size_{other.size_} {
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

    ~List() {
        clear();
    }

    void push(const T& value) {
        Node* const new_node{new Node{value, tail_, nullptr}};
        if (tail_ == nullptr) {
            head_ = new_node;
        } else {
            tail_->next = new_node;
        }
        tail_ = new_node;
        ++size_;
    }

    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty list");
        }

        Node* const old_tail{tail_};
        const T ret_val{old_tail->data};

        tail_ = tail_->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete old_tail;
        --size_;
        return ret_val;
    }

    void unshift(const T& value) {
        Node* const new_node{new Node{value, nullptr, head_}};
        if (head_ == nullptr) {
            tail_ = new_node;
        } else {
            head_->prev = new_node;
        }
        head_ = new_node;
        ++size_;
    }

    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty list");
        }

        Node* const old_head{head_};
        const T ret_val{old_head->data};

        head_ = head_->next;
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
        for (Node* node_itr{head_}; node_itr != nullptr; node_itr = node_itr->next) {
            if (node_itr->data == value) {
                if (node_itr->prev != nullptr) {
                    node_itr->prev->next = node_itr->next;
                } else {
                    head_ = node_itr->next;
                }

                if (node_itr->next != nullptr) {
                    node_itr->next->prev = node_itr->prev;
                } else {
                    tail_ = node_itr->prev;
                }

                delete node_itr;
                --size_;
                return true;
            }
        }
        return false;
    }

    std::uint32_t count() const noexcept {
        return size_;
    }

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    Node* head_;
    Node* tail_;
    std::uint32_t size_;

    void clear() noexcept {
        while (head_ != nullptr) {
            Node* const tmp{head_};
            head_ = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0U;
    }
};

}  // namespace linked_list
