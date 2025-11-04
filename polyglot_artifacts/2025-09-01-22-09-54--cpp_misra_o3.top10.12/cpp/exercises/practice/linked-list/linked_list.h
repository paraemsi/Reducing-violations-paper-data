#pragma once

#include <cstddef>      // for std::size_t
#include <stdexcept>    // for std::out_of_range
#include <utility>      // for std::move

namespace linked_list {

/**
 * @brief A doubly-linked list implemented as a template class.
 *
 * @tparam T Type of the values stored in the list.
 */
template <typename T>
class List
{
private:
    struct Node
    {
        T       value {};
        Node*   prev  {nullptr};
        Node*   next  {nullptr};

        explicit Node(const T& v, Node* p, Node* n) : value(v), prev(p), next(n) {}
        explicit Node(T&& v, Node* p, Node* n) : value(std::move(v)), prev(p), next(n) {}
    };

    Node*       head_ {nullptr};
    Node*       tail_ {nullptr};
    std::size_t size_ {0U};

    /* helper to delete all nodes (used by destructor) */
    void clear() noexcept
    {
        Node* current {head_};
        while (current != nullptr) {
            Node* const nextNode {current->next};
            delete current;
            current = nextNode;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

public:
    List() noexcept = default;

    /* Rule-of-five: disable copy, allow move */
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            clear();
            head_      = other.head_;
            tail_      = other.tail_;
            size_      = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    ~List() noexcept
    {
        clear();
    }

    /* Adds an element to the end of the list. */
    void push(const T& value)
    {
        Node* const newNode {new Node(value, tail_, nullptr)};
        if (tail_ == nullptr) {
            /* List was empty */
            head_ = newNode;
            tail_ = newNode;
        } else {
            tail_->next = newNode;
            tail_ = newNode;
        }
        ++size_;
    }

    /* Adds an element to the start of the list (rvalue overload). */
    void unshift(T&& value)
{
    Node* const newNode {new Node(std::move(value), nullptr, head_)};
    if (head_ == nullptr) {
        /* List was empty */
        head_ = newNode;
        tail_ = newNode;
    } else {
        head_->prev = newNode;
        head_ = newNode;
    }
    ++size_;
}

   /* Adds an element to the end of the list (rvalue overload). */
   void push(T&& value)
    {
        Node* const newNode {new Node(std::move(value), tail_, nullptr)};
        if (tail_ == nullptr) {
            /* List was empty */
            head_ = newNode;
            tail_ = newNode;
        } else {
            tail_->next = newNode;
            tail_ = newNode;
        }
        ++size_;
    }

    /* Removes and returns the last element. */
    T pop()
    {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty list");
        }

        Node* const nodeToRemove {tail_};
        T           retVal       {std::move(nodeToRemove->value)};

        tail_ = tail_->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            /* List became empty */
            head_ = nullptr;
        }
        delete nodeToRemove;
        --size_;
        return retVal;
    }

    /* Removes and returns the first element. */
    T shift()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty list");
        }

        Node* const nodeToRemove {head_};
        T           retVal       {std::move(nodeToRemove->value)};

        head_ = head_->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            /* List became empty */
            tail_ = nullptr;
        }
        delete nodeToRemove;
        --size_;
        return retVal;
    }

    /* Adds an element to the start of the list. */
    void unshift(const T& value)
    {
        Node* const newNode {new Node(value, nullptr, head_)};
        if (head_ == nullptr) {
            /* List was empty */
            head_ = newNode;
            tail_ = newNode;
        } else {
            head_->prev = newNode;
            head_ = newNode;
        }
        ++size_;
    }

    /* Returns the number of elements currently stored. */
    [[nodiscard]] std::size_t count() const noexcept
    {
        return size_;
    }

    /**
     * @brief Remove the first occurrence of value from the list.
     *
     * @param value Value to remove (compares with operator==).
     * @return true  Element was found and removed.
     * @return false Element not present.
     */
    bool erase(const T& value)
    {
        Node* current {head_};
        while (current != nullptr) {
            if (current->value == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    /* Removing head */
                    head_ = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    /* Removing tail */
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
};

}  // namespace linked_list
