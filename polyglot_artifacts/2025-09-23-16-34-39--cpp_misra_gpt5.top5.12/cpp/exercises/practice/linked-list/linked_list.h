#pragma once

#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List final {
private:
    struct Node final {
        T value;
        Node* prev;
        Node* next;

        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {
        }

        explicit Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {
        }
    };

    Node* head_;
    Node* tail_;
    std::uint32_t size_;

    void clear() noexcept {
        Node* current = head_;
        while (current != nullptr) {
            Node* const next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

public:
    List() : head_(nullptr), tail_(nullptr), size_(0U) {
    }

    ~List() {
        clear();
    }

    List(const List&) = delete;
    List& operator=(const List&) = delete;
    List(List&&) = delete;
    List& operator=(List&&) = delete;

    void push(const T& value) {
        Node* const node = new Node(value);
        if ((tail_) == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    void push(T&& value) {
        Node* const node = new Node(std::move(value));
        if ((tail_) == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    T pop() {
        if ((tail_) == nullptr) {
            throw std::out_of_range("pop from empty List");
        }

        Node* const node = tail_;
        T result = std::move(node->value);

        if ((node->prev) != nullptr) {
            tail_ = node->prev;
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
            tail_ = nullptr;
        }

        delete node;
        --size_;
        return result;
    }

    void unshift(const T& value) {
        Node* const node = new Node(value);
        if ((head_) == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }

    void unshift(T&& value) {
        Node* const node = new Node(std::move(value));
        if ((head_) == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }

    T shift() {
        if ((head_) == nullptr) {
            throw std::out_of_range("shift from empty List");
        }

        Node* const node = head_;
        T result = std::move(node->value);

        if ((node->next) != nullptr) {
            head_ = node->next;
            head_->prev = nullptr;
        } else {
            head_ = nullptr;
            tail_ = nullptr;
        }

        delete node;
        --size_;
        return result;
    }

    std::uint32_t count() const noexcept {
        return size_;
    }

    bool erase(const T& value) {
        Node* current = head_;
        while (current != nullptr) {
            if ((current->value == value)) {
                Node* const prev = current->prev;
                Node* const next = current->next;

                if (prev != nullptr) {
                    prev->next = next;
                } else {
                    head_ = next;
                }

                if (next != nullptr) {
                    next->prev = prev;
                } else {
                    tail_ = prev;
                }

                delete current;
                --size_;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
