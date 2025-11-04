#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List
{
private:
    struct Node
    {
        T value;
        Node* prev;
        Node* next;

        template <typename U>
        explicit Node(U&& val, Node* prev_node, Node* next_node)
            : value(std::forward<U>(val)), prev(prev_node), next(next_node)
        {
        }
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t count_{0U};

    void unlink_node(Node* node) noexcept
    {
        if(node == nullptr)
        {
            return;
        }

        if(node->prev != nullptr)
        {
            node->prev->next = node->next;
        }
        else
        {
            head_ = node->next;
        }

        if(node->next != nullptr)
        {
            node->next->prev = node->prev;
        }
        else
        {
            tail_ = node->prev;
        }

        delete node;
        --count_;
    }

public:
    List() = default;
    List(const List& other)
    {
        Node* current = other.head_;
        while(current != nullptr)
        {
            push(current->value);
            current = current->next;
        }
    }
    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), count_(other.count_)
    {
        other.head_  = nullptr;
        other.tail_  = nullptr;
        other.count_ = 0U;
    }

    auto operator=(const List& other) -> List&
    {
        if(this != &other)
        {
            List temp(other);
            swap(temp);
        }
        return *this;
    }
    auto operator=(List&& other) noexcept -> List&
    {
        if(this != &other)
        {
            clear();
            head_  = other.head_;
            tail_  = other.tail_;
            count_ = other.count_;

            other.head_  = nullptr;
            other.tail_  = nullptr;
            other.count_ = 0U;
        }
        return *this;
    }

    ~List()
    {
        clear();
    }

    auto count() const noexcept -> std::size_t
    {
        return count_;
    }

    template <typename U>
    void push(U&& value)
    {
        Node* node = new Node(std::forward<U>(value), tail_, nullptr);

        if(tail_ != nullptr)
        {
            tail_->next = node;
        }
        else
        {
            head_ = node;
        }

        tail_ = node;
        ++count_;
    }

    auto pop() -> T
    {
        if(count_ == static_cast<std::size_t>(0))
        {
            throw std::out_of_range("pop from empty list");
        }

        Node* node = tail_;
        T      val = std::move(node->value);

        tail_ = node->prev;

        if(tail_ != nullptr)
        {
            tail_->next = nullptr;
        }
        else
        {
            head_ = nullptr;
        }

        delete node;
        --count_;
        return val;
    }

    template <typename U>
    void unshift(U&& value)
    {
        Node* node = new Node(std::forward<U>(value), nullptr, head_);

        if(head_ != nullptr)
        {
            head_->prev = node;
        }
        else
        {
            tail_ = node;
        }

        head_ = node;
        ++count_;
    }

    auto shift() -> T
    {
        if(count_ == static_cast<std::size_t>(0))
        {
            throw std::out_of_range("shift from empty list");
        }

        Node* node = head_;
        T      val = std::move(node->value);

        head_ = node->next;

        if(head_ != nullptr)
        {
            head_->prev = nullptr;
        }
        else
        {
            tail_ = nullptr;
        }

        delete node;
        --count_;
        return val;
    }

    auto erase(const T& value) -> bool
    {
        Node* current = head_;
        while(current != nullptr)
        {
            if(current->value == value)
            {
                unlink_node(current);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() noexcept
    {
        Node* current = head_;
        while(current != nullptr)
        {
            Node* const next_node = current->next;
            delete current;
            current = next_node;
        }
        head_  = nullptr;
        tail_  = nullptr;
        count_ = 0U;
    }

    void swap(List& other) noexcept
    {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(count_, other.count_);
    }
};

}  // namespace linked_list
