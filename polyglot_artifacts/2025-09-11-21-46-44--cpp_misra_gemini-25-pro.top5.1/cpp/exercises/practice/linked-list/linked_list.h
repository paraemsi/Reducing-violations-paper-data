#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* next{nullptr};
        Node* prev{nullptr};

        explicit Node(T val) : value(std::move(val)) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::uint64_t count_{0};

public:
    List() = default;

    ~List() {
        while (head_ != nullptr) {
            Node* current = head_;
            head_ = (head_->next);
            delete current;
        }
    }

    List(const List&) = delete;
    List& operator=(const List&) = delete;
    List(List&&) = delete;
    List& operator=(List&&) = delete;

    void push(T value) {
        Node* new_node = new Node(std::move(value));
        if (tail_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            (tail_->next) = new_node;
            (new_node->prev) = tail_;
            tail_ = new_node;
        }
        count_ = (count_ + 1ULL);
    }

    T pop() {
        if (tail_ == nullptr) {
            throw std::runtime_error("List is empty");
        }

        T value = std::move(tail_->value);
        Node* to_delete = tail_;

        if (head_ == tail_) {
            head_ = nullptr;
            tail_ = nullptr;
        } else {
            tail_ = (tail_->prev);
            (tail_->next) = nullptr;
        }

        delete to_delete;
        count_ = (count_ - 1ULL);
        return value;
    }

    void unshift(T value) {
        Node* new_node = new Node(std::move(value));
        if (head_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            (head_->prev) = new_node;
            (new_node->next) = head_;
            head_ = new_node;
        }
        count_ = (count_ + 1ULL);
    }

    T shift() {
        if (head_ == nullptr) {
            throw std::runtime_error("List is empty");
        }

        T value = std::move(head_->value);
        Node* to_delete = head_;

        if (head_ == tail_) {
            head_ = nullptr;
            tail_ = nullptr;
        } else {
            head_ = (head_->next);
            (head_->prev) = nullptr;
        }

        delete to_delete;
        count_ = (count_ - 1ULL);
        return value;
    }

    std::uint64_t count() const {
        return count_;
    }

    bool erase(T value) {
        Node* current = head_;
        while (current != nullptr) {
            if ((current->value) == value) {
                if ((current->prev) != nullptr) {
                    (current->prev->next) = (current->next);
                } else {
                    head_ = (current->next);
                }

                if ((current->next) != nullptr) {
                    (current->next->prev) = (current->prev);
                } else {
                    tail_ = (current->prev);
                }

                delete current;
                count_ = (count_ - 1ULL);
                return true;
            }
            current = (current->next);
        }
        return false;
    }
};

}  // namespace linked_list
