#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T          value;
        Node*      prev;
        Node*      next;

        explicit Node(const T& v, Node* p = nullptr, Node* n = nullptr) :
            value(v),
            prev(p),
            next(n)
        {
        }
    };

    Node*         head_ {nullptr};
    Node*         tail_ {nullptr};
    std::size_t   size_ {0U};

    void clear() noexcept
    {
        while (head_ != nullptr) {
            Node* const old_head {head_};
            head_ = head_->next;
            delete old_head;
        }
        tail_ = nullptr;
        size_ = 0U;
    }

public:
    List() = default;

    /* Deep-copy constructor */
    List(const List& other)
    {
        for (Node* curr {other.head_}; curr != nullptr; curr = curr->next) {
            /* push can throw; guarantee strong exception-safety by
               performing all allocations first, then linking afterwards */
            push(curr->value);
        }
    }

    /* Deep-copy assignment operator */
    List& operator=(const List& other)
    {
        if (this != &other) {
            clear();
            for (Node* curr {other.head_}; curr != nullptr; curr = curr->next) {
                push(curr->value);
            }
        }
        return *this;
    }

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

    ~List()
    {
        clear();
    }

    void push(const T& value)
    {
        Node* const node {new Node(value, tail_, nullptr)};
        if (tail_ != nullptr) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        ++size_;
    }

    T pop()
    {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty list");
        }
        Node* const node {tail_};
        T           result {node->value};
        tail_ = tail_->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete node;
        --size_;
        return result;
    }

    void unshift(const T& value)
    {
        Node* const node {new Node(value, nullptr, head_)};
        if (head_ != nullptr) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        ++size_;
    }

    T shift()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty list");
        }
        Node* const node {head_};
        T           result {node->value};
        head_ = head_->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return result;
    }

    std::size_t count() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        for (Node* current {head_}; current != nullptr; current = current->next) {
            if (current->value == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head_ = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail_ = current->prev;
                }

                delete current;
                --size_;
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
