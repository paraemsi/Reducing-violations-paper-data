#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List
{
public:
    List() noexcept : head_{nullptr}, tail_{nullptr}, size_{static_cast<std::size_t>(0U)} {}

    ~List() noexcept
    {
        Node* current{head_};
        while (current != nullptr)
        {
            Node* const next{current->next};
            delete current;
            current = next;
        }
    }

    List(const List& other) : head_{nullptr}, tail_{nullptr}, size_{static_cast<std::size_t>(0U)}
    {
        Node* current{other.head_};
        while (current != nullptr)
        {
            push(current->data);
            current = current->next;
        }
    }

    List(List&& other) noexcept : head_{other.head_}, tail_{other.tail_}, size_{other.size_}
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }

    List& operator=(const List& other)
    {
        if (this != &other)
        {
            clear();
            Node* current{other.head_};
            while (current != nullptr)
            {
                push(current->data);
                current = current->next;
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
            other.size_ = static_cast<std::size_t>(0U);
        }
        return *this;
    }

    void push(const T& value)
    {
        Node* const node{new Node(value)};
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


    void unshift(const T& value)
    {
        Node* const node{new Node(value)};
        if (head_ == nullptr)
        {
            head_ = node;
            tail_ = node;
        }
        else
        {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }


    T pop()
    {
        if (tail_ == nullptr)
        {
            throw std::out_of_range("pop on empty list");
        }
        Node* const node{tail_};
        T value{std::move(node->data)};
        tail_ = node->prev;
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

    T shift()
    {
        if (head_ == nullptr)
        {
            throw std::out_of_range("shift on empty list");
        }
        Node* const node{head_};
        T value{std::move(node->data)};
        head_ = node->next;
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

    bool erase(const T& value) noexcept
    {
        Node* current{head_};
        while (current != nullptr)
        {
            if (current->data == value)
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }
                else
                {
                    head_ = current->next;
                }

                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }
                else
                {
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

    [[nodiscard]] std::size_t count() const noexcept
    {
        return size_;
    }

private:
    struct Node
    {
        explicit Node(const T& d) : data{d}, next{nullptr}, prev{nullptr} {}
        T data;
        Node* next;
        Node* prev;
    };

    void clear() noexcept
    {
        Node* current{head_};
        while (current != nullptr)
        {
            Node* const next{current->next};
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::size_t>(0U);
    }

    Node* head_;
    Node* tail_;
    std::size_t size_;
};

}  // namespace linked_list
