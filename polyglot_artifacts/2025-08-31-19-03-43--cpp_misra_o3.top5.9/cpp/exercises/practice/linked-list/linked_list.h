#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <utility>   // for std::move

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node* prev;

        explicit Node(const T& value)
            : data(value),
              next(nullptr),
              prev(nullptr) {}
    };

    std::unique_ptr<Node> head_;
    Node* tail_;
    std::uint32_t size_;

public:
    List() noexcept
        : head_(nullptr),
          tail_(nullptr),
          size_(0U) {}

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept
        : head_(std::move(other.head_)),
          tail_(other.tail_),
          size_(other.size_) {
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            head_ = std::move(other.head_);
            tail_ = other.tail_;
            size_ = other.size_;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    ~List() = default;

    void push(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        new_node->prev = tail_;
        Node* const new_tail = new_node.get();

        if (tail_ == nullptr) {
            head_ = std::move(new_node);
        } else {
            tail_->next = std::move(new_node);
        }
        tail_ = new_tail;
        ++size_;
    }

    T pop() {
        if (size_ == 0U) {
            throw std::out_of_range("pop from empty list");
        }

        Node* const old_tail = tail_;
        T ret = old_tail->data;

        if (old_tail->prev == nullptr) {
            head_.reset();
            tail_ = nullptr;
        } else {
            tail_ = old_tail->prev;
            tail_->next.reset();
        }
        --size_;
        return ret;
    }

    void unshift(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        new_node->next = std::move(head_);

        if (new_node->next != nullptr) {
            new_node->next->prev = new_node.get();
        } else {
            tail_ = new_node.get();
        }

        head_ = std::move(new_node);
        ++size_;
    }

    T shift() {
        if (size_ == 0U) {
            throw std::out_of_range("shift from empty list");
        }

        auto old_head = std::move(head_);
        head_ = std::move(old_head->next);

        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        --size_;
        return old_head->data;
    }

    std::uint32_t count() const noexcept {
        return size_;
    }

    bool erase(const T& value) {
        Node* current = head_.get();

        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev == nullptr) {
                    static_cast<void>(this->shift());
                } else if (current->next == nullptr) {
                    static_cast<void>(this->pop());
                } else {
                    Node* const prev_node = current->prev;
                    std::unique_ptr<Node> temp = std::move(prev_node->next);
                    prev_node->next = std::move(temp->next);
                    if (prev_node->next != nullptr) {
                        prev_node->next->prev = prev_node;
                    }
                    --size_;
                }
                return true;
            }
            current = current->next.get();
        }
        return false;
    }
};

}  // namespace linked_list
