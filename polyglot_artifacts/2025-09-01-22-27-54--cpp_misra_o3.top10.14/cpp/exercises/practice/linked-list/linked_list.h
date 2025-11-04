#pragma once

#include <cstdint>
#include <memory>
#include <utility>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;
        Node* prev;

        explicit Node(const T& value, Node* prev_node) : data(value), next(nullptr), prev(prev_node) {}
    };

    std::unique_ptr<Node> head_;
    Node* tail_;
    std::uint32_t size_;

public:
    List() : head_(nullptr), tail_(nullptr), size_(static_cast<std::uint32_t>(0U)) {}
    ~List() = default; /* unique_ptr handles cleanup */

    void push(const T& value)
    {
        if(head_ == nullptr)
        {
            head_ = std::make_unique<Node>(value, nullptr);
            tail_ = head_.get();
        }
        else
        {
            Node* old_tail = tail_;
            old_tail->next = std::make_unique<Node>(value, old_tail);
            tail_ = old_tail->next.get();
        }
        ++size_;
    }

    T pop()
    {
        if(size_ == static_cast<std::uint32_t>(0U))
        {
            throw std::out_of_range("pop on empty list");
        }

        Node* node_to_remove = tail_;
        T ret_val = node_to_remove->data;

        if(node_to_remove->prev == nullptr)
        {
            head_.reset();
            tail_ = nullptr;
        }
        else
        {
            Node* new_tail = node_to_remove->prev;
            new_tail->next.reset();
            tail_ = new_tail;
        }
        --size_;
        return ret_val;
    }

    void unshift(const T& value)
    {
        std::unique_ptr<Node> new_head = std::make_unique<Node>(value, nullptr);
        if(head_ == nullptr)
        {
            tail_ = new_head.get();
        }
        else
        {
            head_->prev = new_head.get();
            new_head->next = std::move(head_);
        }
        head_ = std::move(new_head);
        ++size_;
    }

    T shift()
    {
        if(size_ == static_cast<std::uint32_t>(0U))
        {
            throw std::out_of_range("shift on empty list");
        }

        std::unique_ptr<Node> old_head = std::move(head_);
        T ret_val = old_head->data;
        head_ = std::move(old_head->next);
        if(head_ != nullptr)
        {
            head_->prev = nullptr;
        }
        else
        {
            tail_ = nullptr;
        }
        --size_;
        return ret_val;
    }

    bool erase(const T& value)
    {
        Node* curr = head_.get();
        while(curr != nullptr)
        {
            if(curr->data == value)
            {
                if(curr->prev == nullptr)
                {
                    (void)shift();
                }
                else if(curr->next == nullptr)
                {
                    (void)pop();
                }
                else
                {
                    Node* prev_node = curr->prev;
                    std::unique_ptr<Node> orphan = std::move(prev_node->next);
                    prev_node->next = std::move(orphan->next);
                    if(prev_node->next != nullptr)
                    {
                        prev_node->next->prev = prev_node;
                    }
                    --size_;
                }
                return true;
            }
            curr = curr->next.get();
        }
        return false;
    }

    std::uint32_t count() const noexcept
    {
        return size_;
    }

    /* Disallow copying to avoid inadvertent expensive operations */
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    /* Allow move semantics */
    List(List&&) noexcept = default;
    List& operator=(List&&) noexcept = default;
};

} /* namespace linked_list */
