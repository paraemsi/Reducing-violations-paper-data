#pragma once

#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List
{
public:
    using size_type = std::uint32_t;

    List() noexcept : head_{nullptr}, tail_{nullptr}, size_{0U} {}

    List(const List& other) : List()
    {
        for (Node* cur = other.head_; cur != nullptr; cur = cur->next)
        {
            push(cur->data);
        }
    }

    List(List&& other) noexcept : head_{other.head_}, tail_{other.tail_}, size_{other.size_}
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(const List& other)
    {
        if (this != &other)
        {
            clear();
            for (Node* cur = other.head_; cur != nullptr; cur = cur->next)
            {
                push(cur->data);
            }
        }
        return *this;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other)
        {
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

    ~List()
    {
        clear();
    }

    void push(const T& value)
    {
        Node* node = new Node(value);
        if (tail_ == nullptr)
        {
            head_ = node;
            tail_ = node;
        }
        else
        {
            tail_->next = node;
            node->prev = tail_;
            tail_ = node;
        }
        ++size_;
    }

    T pop()
    {
        if (tail_ == nullptr)
        {
            throw std::out_of_range("pop on empty list");
        }

        Node* node = tail_;
        T value = std::move(node->data);

        tail_ = tail_->prev;
        if (tail_ != nullptr)
        {
            tail_->next = nullptr;
        }
        else
        {
            head_ = nullptr;
        }

        delete node;
        --size_;
        return value;
    }

    void unshift(const T& value)
    {
        Node* node = new Node(value);
        if (head_ == nullptr)
        {
            head_ = node;
            tail_ = node;
        }
        else
        {
            head_->prev = node;
            node->next = head_;
            head_ = node;
        }
        ++size_;
    }

    T shift()
    {
        if (head_ == nullptr)
        {
            throw std::out_of_range("shift on empty list");
        }

        Node* node = head_;
        T value = std::move(node->data);

        head_ = head_->next;
        if (head_ != nullptr)
        {
            head_->prev = nullptr;
        }
        else
        {
            tail_ = nullptr;
        }

        delete node;
        --size_;
        return value;
    }

    bool erase(const T& value)
    {
        for (Node* cur = head_; cur != nullptr; cur = cur->next)
        {
            if (cur->data == value)
            {
                if (cur->prev != nullptr)
                {
                    cur->prev->next = cur->next;
                }
                else
                {
                    head_ = cur->next;
                }

                if (cur->next != nullptr)
                {
                    cur->next->prev = cur->prev;
                }
                else
                {
                    tail_ = cur->prev;
                }

                delete cur;
                --size_;
                return true;
            }
        }
        return false;
    }

    size_type count() const noexcept
    {
        return size_;
    }

private:
    struct Node
    {
        explicit Node(const T& v) : data{v}, prev{nullptr}, next{nullptr} {}
        T data;
        Node* prev;
        Node* next;
    };

    void clear() noexcept
    {
        Node* cur = head_;
        while (cur != nullptr)
        {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

    Node* head_;
    Node* tail_;
    size_type size_;
};

}  // namespace linked_list
