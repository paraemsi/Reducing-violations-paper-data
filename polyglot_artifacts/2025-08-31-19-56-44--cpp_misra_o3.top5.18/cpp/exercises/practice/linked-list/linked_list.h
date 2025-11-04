#pragma once

#include <cstddef>      // for std::size_t
#include <cstdint>      // fixed-width integer types, MISRA compliant
#include <stdexcept>    // for std::out_of_range
#include <utility>      // for std::move

namespace linked_list {

template <typename T>
class List
{
private:
    struct Node
    {
        /* Initialization order must match declaration order to satisfy
         * strict compiler warnings (-Wreorder) and MISRA recommendations.
         * Members are declared as: next, prev, value.
         */
        explicit Node(const T& v) : next(nullptr), prev(nullptr), value(v) {}
        Node* next;
        Node* prev;
        T      value;
    };

    Node*        head_;
    Node*        tail_;
    std::size_t  count_;

    // helper to delete all nodes
    void clear() noexcept
    {
        Node* current = head_;
        while (current != nullptr)
        {
            Node* const next_node = current->next;
            delete current;
            current = next_node;
        }
        head_  = nullptr;
        tail_  = nullptr;
        count_ = static_cast<std::size_t>(0U);
    }

public:
    List() : head_(nullptr), tail_(nullptr), count_(static_cast<std::size_t>(0U)) {}

    ~List()
    {
        clear();
    }

    // number of elements
    std::size_t count() const noexcept
    {
        return count_;
    }

    // add to end
    void push(const T& value)
    {
        Node* const new_node = new Node(value);
        if (head_ == nullptr)
        {
            head_ = new_node;
            tail_ = new_node;
        }
        else
        {
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
        }
        ++count_;
    }

    // add to front
    void unshift(const T& value)
    {
        Node* const new_node = new Node(value);
        if (head_ == nullptr)
        {
            head_ = new_node;
            tail_ = new_node;
        }
        else
        {
            new_node->next = head_;
            head_->prev = new_node;
            head_ = new_node;
        }
        ++count_;
    }

    // remove last and return it
    T pop()
    {
        if (tail_ == nullptr)
        {
            throw std::out_of_range("List::pop on empty list");
        }

        Node* const old_tail = tail_;
        tail_ = tail_->prev;
        if (tail_ != nullptr)
        {
            tail_->next = nullptr;
        }
        else
        {
            head_ = nullptr;   // list became empty
        }

        T result = std::move(old_tail->value);
        delete old_tail;
        --count_;
        return result;
    }

    // remove first and return it
    T shift()
    {
        if (head_ == nullptr)
        {
            throw std::out_of_range("List::shift on empty list");
        }

        Node* const old_head = head_;
        head_ = head_->next;
        if (head_ != nullptr)
        {
            head_->prev = nullptr;
        }
        else
        {
            tail_ = nullptr;   // list became empty
        }

        T result = std::move(old_head->value);
        delete old_head;
        --count_;
        return result;
    }

    // remove first occurrence of value, return true if removed
    bool erase(const T& value)
    {
        Node* current = head_;
        while (current != nullptr)
        {
            if (current->value == value)
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }
                else
                {
                    head_ = current->next;   // removing head
                }

                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }
                else
                {
                    tail_ = current->prev;   // removing tail
                }

                delete current;
                --count_;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // disable copy semantics
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // enable move semantics
    List(List&& other) noexcept :
        head_(other.head_), tail_(other.tail_), count_(other.count_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.count_ = static_cast<std::size_t>(0U);
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            head_  = other.head_;
            tail_  = other.tail_;
            count_ = other.count_;
            other.head_  = nullptr;
            other.tail_  = nullptr;
            other.count_ = static_cast<std::size_t>(0U);
        }
        return *this;
    }
};

}  // namespace linked_list
