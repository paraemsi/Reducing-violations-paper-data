#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

// Doubly-linked list implemented as a class template.
// Only standard library headers are used and MISRA-style rules are respected.
template <typename T>
class List {
private:
    struct Node {
        T       value;
        Node*   prev;
        Node*   next;

        explicit Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
        explicit Node(T&&  val)     : value(std::move(val)), prev(nullptr), next(nullptr) {}

        Node(const Node&)            = delete;
        Node& operator=(const Node&) = delete;
    };

    Node*       head_;
    Node*       tail_;
    std::size_t size_;

    void remove_node(Node* node)
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
        --size_;
    }

    void copy_from(const List& other)
    {
        for(Node* cur = other.head_; cur != nullptr; cur = cur->next)
        {
            push(cur->value);
        }
    }

public:
    List() : head_(nullptr), tail_(nullptr), size_(0U) {}

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0U)
    {
        copy_from(other);
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(const List& other)
    {
        if(this != &other)
        {
            clear();
            copy_from(other);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept
    {
        if(this != &other)
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

    // Add element to the end.
    void push(const T& value)
    {
        Node* n = new Node(value);
        if(tail_ == nullptr)
        {
            head_ = n;
            tail_ = n;
        }
        else
        {
            tail_->next = n;
            n->prev     = tail_;
            tail_       = n;
        }
        ++size_;
    }

    void push(T&& value)
    {
        Node* n = new Node(std::move(value));
        if(tail_ == nullptr)
        {
            head_ = n;
            tail_ = n;
        }
        else
        {
            tail_->next = n;
            n->prev     = tail_;
            tail_       = n;
        }
        ++size_;
    }

    // Remove and return element from the end.
    T pop()
    {
        if(tail_ == nullptr)
        {
            throw std::out_of_range("pop from empty list");
        }

        Node* n   = tail_;
        T     val = std::move(n->value);

        tail_ = n->prev;
        if(tail_ != nullptr)
        {
            tail_->next = nullptr;
        }
        else
        {
            head_ = nullptr;
        }

        delete n;
        --size_;
        return val;
    }

    // Add element to the front.
    void unshift(const T& value)
    {
        Node* n = new Node(value);
        if(head_ == nullptr)
        {
            head_ = n;
            tail_ = n;
        }
        else
        {
            n->next   = head_;
            head_->prev = n;
            head_     = n;
        }
        ++size_;
    }

    void unshift(T&& value)
    {
        Node* n = new Node(std::move(value));
        if(head_ == nullptr)
        {
            head_ = n;
            tail_ = n;
        }
        else
        {
            n->next   = head_;
            head_->prev = n;
            head_     = n;
        }
        ++size_;
    }

    // Remove and return element from the front.
    T shift()
    {
        if(head_ == nullptr)
        {
            throw std::out_of_range("shift from empty list");
        }

        Node* n   = head_;
        T     val = std::move(n->value);

        head_ = n->next;
        if(head_ != nullptr)
        {
            head_->prev = nullptr;
        }
        else
        {
            tail_ = nullptr;
        }

        delete n;
        --size_;
        return val;
    }

    // Remove first occurrence of value; return true if removed.
    bool erase(const T& value)
    {
        for(Node* cur = head_; cur != nullptr; cur = cur->next)
        {
            if(cur->value == value)
            {
                remove_node(cur);
                return true;
            }
        }
        return false;
    }

    // Number of elements in the list.
    std::size_t count() const
    {
        return size_;
    }

    // Clear entire list.
    void clear()
    {
        Node* cur = head_;
        while(cur != nullptr)
        {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }
};

}  // namespace linked_list
