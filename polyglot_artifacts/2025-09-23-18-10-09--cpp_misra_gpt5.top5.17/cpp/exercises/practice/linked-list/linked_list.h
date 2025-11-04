#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    List() = default;

    ~List() noexcept
    {
        clear();
    }

    List(const List& other)
        : head_(nullptr)
        , tail_(nullptr)
        , size_(static_cast<std::size_t>(0U))
    {
        copy_from(other);
    }

    List& operator=(const List& other)
    {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    List(List&& other) noexcept
        : head_(nullptr)
        , tail_(nullptr)
        , size_(static_cast<std::size_t>(0U))
    {
        move_from(std::move(other));
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            clear();
            move_from(std::move(other));
        }
        return *this;
    }

    void push(const T& value)
    {
        Node* n = new Node(value);
        if ((tail_ == nullptr)) {
            head_ = n;
            tail_ = n;
        } else {
            n->prev = tail_;
            tail_->next = n;
            tail_ = n;
        }
        ++size_;
    }

    T pop()
    {
        if ((tail_ == nullptr)) {
            throw std::out_of_range("pop on empty List");
        }

        Node* n = tail_;
        T value = n->value;

        tail_ = n->prev;
        if ((tail_ != nullptr)) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete n;
        --size_;
        return value;
    }

    void unshift(const T& value)
    {
        Node* n = new Node(value);
        if ((head_ == nullptr)) {
            head_ = n;
            tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        ++size_;
    }

    T shift()
    {
        if ((head_ == nullptr)) {
            throw std::out_of_range("shift on empty List");
        }

        Node* n = head_;
        T value = n->value;

        head_ = n->next;
        if ((head_ != nullptr)) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete n;
        --size_;
        return value;
    }

    std::size_t count() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        Node* cur = head_;
        while ((cur != nullptr)) {
            if ((cur->value == value)) {
                // unlink cur
                if ((cur->prev != nullptr)) {
                    cur->prev->next = cur->next;
                } else {
                    head_ = cur->next;
                }

                if ((cur->next != nullptr)) {
                    cur->next->prev = cur->prev;
                } else {
                    tail_ = cur->prev;
                }

                delete cur;
                --size_;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

private:
    struct Node {
        explicit Node(const T& v)
            : value(v)
            , prev(nullptr)
            , next(nullptr)
        {
        }
        T value;
        Node* prev;
        Node* next;
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{static_cast<std::size_t>(0U)};

    void clear() noexcept
    {
        Node* cur = head_;
        while ((cur != nullptr)) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::size_t>(0U);
    }

    void copy_from(const List& other)
    {
        Node* cur = other.head_;
        while ((cur != nullptr)) {
            push(cur->value);
            cur = cur->next;
        }
    }

    void move_from(List&& other) noexcept
    {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }
};

}  // namespace linked_list
