#pragma once

#include <cstddef>          // for std::size_t
#include <stdexcept>        // for std::underflow_error
#include <utility>          // for std::move
#include <algorithm>        // for std::swap

namespace linked_list {

// A generic doubly-linked list that provides O(1) insertion/removal at both ends.
// All method bodies are defined in the header so that the template can be used
// without explicit instantiation in the translation unit that includes it.
template <typename T>
class List
{
private:
    struct Node
    {
        T     data;
        Node* prev;
        Node* next;
    };

    Node*       head_;
    Node*       tail_;
    std::size_t size_;

    void clear() noexcept
    {
        Node* current = head_;
        while (current != nullptr)
        {
            Node* const next_node = current->next;
            delete current;
            current = next_node;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

public:
    List() noexcept : head_(nullptr), tail_(nullptr), size_(0U) {}

    // Deep-copy constructor
    List(const List& other) :
        head_(nullptr),
        tail_(nullptr),
        size_(0U)
    {
        Node* current = other.head_;
        while (current != nullptr)
        {
            push(current->data);
            current = current->next;
        }
    }

    // Deep-copy assignment operator (copy-and-swap idiom)
    List& operator=(const List& other)
    {
        if (this != &other)
        {
            List temp(other);
            std::swap(head_, temp.head_);
            std::swap(tail_, temp.tail_);
            std::swap(size_, temp.size_);
        }
        return *this;
    }

    // Enable move semantics
    List(List&& other) noexcept :
        head_(other.head_),
        tail_(other.tail_),
        size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            head_       = other.head_;
            tail_       = other.tail_;
            size_       = other.size_;
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

    // Add to the end of the list.
    void push(const T& value)
    {
        Node* const new_node = new Node{value, tail_, nullptr};
        if (tail_ != nullptr)
        {
            tail_->next = new_node;
        }
        else
        {
            head_ = new_node;
        }
        tail_ = new_node;
        ++size_;
    }

    // Remove and return the last element.
    T pop()
    {
        if (size_ == 0U)
        {
            throw std::underflow_error("pop() called on empty List");
        }

        Node* const node = tail_;
        T const      val = node->data;

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

        return val;
    }

    // Remove and return the first element.
    T shift()
    {
        if (size_ == 0U)
        {
            throw std::underflow_error("shift() called on empty List");
        }

        Node* const node = head_;
        T const      val = node->data;

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

        return val;
    }

    // Add an element to the front of the list.
    void unshift(const T& value)
    {
        Node* const new_node = new Node{value, nullptr, head_};
        if (head_ != nullptr)
        {
            head_->prev = new_node;
        }
        else
        {
            tail_ = new_node;
        }
        head_ = new_node;
        ++size_;
    }

    // Return the number of elements currently stored.
    std::size_t count() const noexcept
    {
        return size_;
    }

    // Remove the first occurrence of 'value'. Return true if something was erased.
    bool erase(const T& value)
    {
        Node* node = head_;
        while (node != nullptr)
        {
            if (node->data == value)
            {
                if (node->prev != nullptr)
                {
                    node->prev->next = node->next;
                }
                else
                {
                    head_ = node->next;
                }

                if (node->next != nullptr)
                {
                    node->next->prev = node->prev;
                }
                else
                {
                    tail_ = node->prev;
                }

                delete node;
                --size_;
                return true;
            }
            node = node->next;
        }
        return false;
    }
};

}  // namespace linked_list
