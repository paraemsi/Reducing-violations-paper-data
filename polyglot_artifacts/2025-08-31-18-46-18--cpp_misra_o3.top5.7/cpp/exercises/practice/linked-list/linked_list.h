#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next { nullptr };
        Node* prev { nullptr };

        explicit Node(const T& value) : data(value) {}
    };

    std::unique_ptr<Node> head_ { nullptr };
    Node* tail_ { nullptr };
    std::uint32_t size_ { 0U };

public:
    List() = default;
    ~List() = default;

    List(const List&) = delete;
    List& operator=(const List&) = delete;
    List(List&&) noexcept = default;
    List& operator=(List&&) noexcept = default;

    void push(const T& value)
    {
        auto new_node = std::make_unique<Node>(value);

        if (size_ == 0U) {
            head_ = std::move(new_node);
            tail_ = head_.get();
        } else {
            new_node->prev = tail_;
            tail_->next = std::move(new_node);
            tail_ = tail_->next.get();
        }

        ++size_;
    }

    T pop()
    {
        if (size_ == 0U) {
            throw std::out_of_range("pop on empty list");
        }

        T value = tail_->data;

        if (tail_->prev == nullptr) {
            head_.reset();
            tail_ = nullptr;
        } else {
            Node* prev_node = tail_->prev;
            prev_node->next.reset();
            tail_ = prev_node;
        }

        --size_;
        return value;
    }

    void unshift(const T& value)
    {
        auto new_node = std::make_unique<Node>(value);
        new_node->next = std::move(head_);

        if (new_node->next != nullptr) {
            new_node->next->prev = new_node.get();
        } else {
            /* list was empty, adjust tail_ */
            tail_ = new_node.get();
        }

        head_ = std::move(new_node);
        ++size_;
    }

    T shift()
    {
        if (size_ == 0U) {
            throw std::out_of_range("shift on empty list");
        }

        T value = head_->data;

        std::unique_ptr<Node> old_head = std::move(head_);
        head_ = std::move(old_head->next);

        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            /* list became empty */
            tail_ = nullptr;
        }

        --size_;
        return value;
    }

    std::uint32_t count() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        Node* current = head_.get();

        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev == nullptr) {
                    /* erase head */
                    (void)shift();
                } else {
                    Node* prev_node = current->prev;
                    std::unique_ptr<Node> removed = std::move(prev_node->next);
                    prev_node->next = std::move(removed->next);

                    if (prev_node->next != nullptr) {
                        prev_node->next->prev = prev_node;
                    } else {
                        /* removed last element */
                        tail_ = prev_node;
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
