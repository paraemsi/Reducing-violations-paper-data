#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    List() noexcept = default;

    ~List()
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
        if ((this != &other)) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    List(List&& other) noexcept
        : head_(other.head_)
        , tail_(other.tail_)
        , size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }

    List& operator=(List&& other) noexcept
    {
        if ((this != &other)) {
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
        append_node(new Node(value));
    }

    void push(T&& value)
    {
        append_node(new Node(std::move(value)));
    }

    T pop()
    {
        if ((tail_ == nullptr)) {
            throw std::out_of_range("pop from empty list");
        }

        Node* node = tail_;
        T value = std::move(node->data);

        tail_ = node->prev;
        if ((tail_ != nullptr)) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete node;
        size_ -= static_cast<std::size_t>(1U);
        return value;
    }

    T shift()
    {
        if ((head_ == nullptr)) {
            throw std::out_of_range("shift from empty list");
        }

        Node* node = head_;
        T value = std::move(node->data);

        head_ = node->next;
        if ((head_ != nullptr)) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete node;
        size_ -= static_cast<std::size_t>(1U);
        return value;
    }

    void unshift(const T& value)
    {
        prepend_node(new Node(value));
    }

    void unshift(T&& value)
    {
        prepend_node(new Node(std::move(value)));
    }

    std::size_t count() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        Node* cur = head_;
        while ((cur != nullptr)) {
            if ((cur->data == value)) {
                remove_node(cur);
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        explicit Node(const T& v)
            : data(v)
            , prev(nullptr)
            , next(nullptr)
        {
        }

        explicit Node(T&& v)
            : data(std::move(v))
            , prev(nullptr)
            , next(nullptr)
        {
        }
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = static_cast<std::size_t>(0U);

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
            push(cur->data);
            cur = cur->next;
        }
    }

    void append_node(Node* node)
    {
        node->prev = tail_;
        node->next = nullptr;

        if ((tail_ != nullptr)) {
            tail_->next = node;
        } else {
            head_ = node;
        }

        tail_ = node;
        size_ += static_cast<std::size_t>(1U);
    }

    void prepend_node(Node* node)
    {
        node->prev = nullptr;
        node->next = head_;

        if ((head_ != nullptr)) {
            head_->prev = node;
        } else {
            tail_ = node;
        }

        head_ = node;
        size_ += static_cast<std::size_t>(1U);
    }

    void remove_node(Node* node)
    {
        Node* prev = node->prev;
        Node* next = node->next;

        if ((prev != nullptr)) {
            prev->next = next;
        } else {
            head_ = next;
        }

        if ((next != nullptr)) {
            next->prev = prev;
        } else {
            tail_ = prev;
        }

        delete node;
        size_ -= static_cast<std::size_t>(1U);
    }
};

}  // namespace linked_list
